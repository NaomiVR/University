using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
public class MarchingCubes : MonoBehaviour
{
	[Header("Grid")] 
	[SerializeField] [Range(1, 40)] public int gridSizeX = 40;
	[SerializeField] [Range(1, 40)] public int gridSizeY = 40;
	[SerializeField] [Range(1, 40)] public int gridSizeZ = 40;
	
	[Header("Noise")]
	[SerializeField] [Range(2f, 10f)] public float isoValue = 2f;
	[SerializeField] [Range(2.5f, 20f)] public float noiseScale = 2.5f;
	[SerializeField] [Range(3f, 10f)] public float noiseAmplitude = 3f;
	
	[Header("Mesh")] 
	[SerializeField] private Mesh mesh; 
	[SerializeField] private MeshFilter meshFilter; 
	[SerializeField] private List<Vector3> vertices = new List<Vector3>(); 
	[SerializeField] private List<int> triangles = new List<int>(); 
	[SerializeField] private Color[] colours; 
	private float[,,] _densityGrid;
	
	public void SetGridX(string sizeX) 
	{ 
		gridSizeX = int.Parse(sizeX); 
	}
	
	public void SetGridY(string sizeY) 
	{ 
		gridSizeY = int.Parse(sizeY); 
	}
	
	public void SetGridZ(string sizeZ) 
	{ 
		gridSizeZ = int.Parse(sizeZ); 
	}
	
	public void SetIsoValue(string value) 
	{ 
		isoValue = float.Parse(value); 
	}
	
	public void SetNoiseScale(string scale) 
	{ 
		noiseScale = float.Parse(scale); 
	}
	
	public void SetNoiseAmplitude(string amplitude) 
	{ 
		noiseAmplitude = float.Parse(amplitude); 
	}
	
	public void OnClick() 
	{ 
		mesh = new Mesh(); 
		meshFilter = GetComponent<MeshFilter>();
		
		InitialiseDensityGrid(); 
		GenerateMesh(); 
	}
	
	private void InitialiseDensityGrid() 
	{ 
		_densityGrid = new float[gridSizeX, gridSizeY, gridSizeZ];
		
		for (int x = 0; x < gridSizeX; x++) 
		{ 
			for (int y = 0; y < gridSizeY; y++) 
			{ 
				for (int z = 0; z < gridSizeZ; z++) 
				{ 
					float noiseValue = PerlinNoise(
						(float)x / gridSizeX * noiseScale, 
						(float)y / gridSizeY * noiseScale, 
						(float)z / gridSizeZ * noiseScale
						) * noiseAmplitude;
					
					_densityGrid[x, y, z] = noiseValue; 
				} 
			} 
		} 
	}
	
	private static float PerlinNoise(float x, float y, float z) 
	{ 
		float xy = Mathf.PerlinNoise(x, y); 
		float xz = Mathf.PerlinNoise(x, z); 
		float yz = Mathf.PerlinNoise(y, z); 
		float yx = Mathf.PerlinNoise(y, x); 
		float zx = Mathf.PerlinNoise(z, x); 
		float zy = Mathf.PerlinNoise(z, y);
		
		return (xy + xz + yz + yx + zx + zy) / 6f; 
	}
	
	private void GenerateMesh() 
	{ 
		for (int x = 0; x < gridSizeX - 1; x++) 
		{ 
			for (int y = 0; y < gridSizeY - 1; y++) 
			{ 
				for (int z = 0; z < gridSizeZ - 1; z++) 
				{ 
					float[] cubeValues = { 
						_densityGrid[x, y, z + 1], 
						_densityGrid[x + 1, y, z + 1], 
						_densityGrid[x + 1, y, z], 
						_densityGrid[x, y, z], 
						_densityGrid[x, y + 1, z + 1], 
						_densityGrid[x + 1, y + 1, z + 1], 
						_densityGrid[x + 1, y + 1, z], 
						_densityGrid[x, y + 1, z] 
					};
					
					int cubeIndex = ClassifyCube(cubeValues); 
					if (cubeIndex is 0 or 255) continue;
					
					int[] configuration = GeometryData.Cases[cubeIndex];
					
					Vector3 worldPos = new Vector3(x, y, z);
					
					CreateTriangles(configuration, cubeValues, worldPos); 
				} 
			} 
		} 
		AssignColour();
		
		mesh.Clear(); 
		mesh.vertices = vertices.ToArray(); 
		mesh.triangles = triangles.ToArray(); 
		mesh.colors = colours; 
		mesh.RecalculateNormals(); 
		meshFilter.mesh = mesh; 
	} 
	
	private int ClassifyCube(float[] cubeValues) 
	{ 
		int cubeIndex = 0; 
		if (cubeValues[0] < isoValue) cubeIndex |= 1; 
		if (cubeValues[1] < isoValue) cubeIndex |= 2; 
		if (cubeValues[2] < isoValue) cubeIndex |= 4; 
		if (cubeValues[3] < isoValue) cubeIndex |= 8; 
		if (cubeValues[4] < isoValue) cubeIndex |= 16; 
		if (cubeValues[5] < isoValue) cubeIndex |= 32; 
		if (cubeValues[6] < isoValue) cubeIndex |= 64; 
		if (cubeValues[7] < isoValue) cubeIndex |= 128;
		
		return cubeIndex; 
	}
	
	private void CreateTriangles(int[] configuration, float[] cubeValues, Vector3 worldPos) 
	{ 
		for (int i = 0; configuration[i] != -1; i+=3) 
		{ 
			int edge01 = GeometryData.Edges[configuration[i]][0]; 
			int edge02 = GeometryData.Edges[configuration[i]][1]; 
			int edge11 = GeometryData.Edges[configuration[i + 1]][0]; 
			int edge12 = GeometryData.Edges[configuration[i + 1]][1]; 
			int edge21 = GeometryData.Edges[configuration[i + 2]][0]; 
			int edge22 = GeometryData.Edges[configuration[i + 2]][1];
			
			Vector3 a = InterpolateVertex(
				GeometryData.Vertices[edge01], 
				GeometryData.Vertices[edge02], 
				cubeValues[edge01], 
				cubeValues[edge02]
				) + worldPos;
			
			Vector3 b = InterpolateVertex(
				GeometryData.Vertices[edge11], 
				GeometryData.Vertices[edge12], 
				cubeValues[edge11], 
				cubeValues[edge12]
				) + worldPos;
			
			Vector3 c = InterpolateVertex(
				GeometryData.Vertices[edge21], 
				GeometryData.Vertices[edge22], 
				cubeValues[edge21], 
				cubeValues[edge22]
				) + worldPos;
			
			AddTriangle(a, b, c);
		}
	}
	
	private Vector3 InterpolateVertex(Vector3 p1, Vector3 p2, float val1, float val2)
	{
		if (Mathf.Abs(isoValue - val1) < 0.0001f) 
		{ 
			return p1; 
		} 
		if (Mathf.Abs(isoValue - val2) < 0.0001f) 
		{ 
			return p2; 
		} 
		if (Mathf.Abs(val1 - val2) < 0.0001f) 
		{ 
			return p1; 
		}
		
		float t = (isoValue - val1) / (val2 - val1);
		Vector3 interpolatedVertex = p1 + t * (p2 - p1);
		
		return interpolatedVertex;
	}
	
	private void AddTriangle(Vector3 a, Vector3 b, Vector3 c)
	{
		int triIndex = triangles.Count;
		vertices.Add(a);
		vertices.Add(b);
		vertices.Add(c);
		triangles.Add(triIndex);
		triangles.Add(triIndex + 1);
		triangles.Add(triIndex + 2);
	}
	
	private void AssignColour()
	{ 
		colours = new Color[triangles.Count];
		
		Color[] colourGradient =
		{
			Color.red, 
			Color.green, 
			Color.blue, 
			Color.yellow, 
			Color.white
		};
		
		for (int i = 0; i < triangles.Count; i++) 
		{ 
			Vector3 vertexPos = vertices[i]; 
			float normalizedY = Mathf.InverseLerp(isoValue - 1.5f, isoValue + 1.5f, vertexPos.y);
			
			normalizedY = Mathf.Clamp01(normalizedY);
			
			int colourIndex = Mathf.FloorToInt(normalizedY * (colourGradient.Length - 1)); 
			Color startColour = colourIndex > 0 ? colourGradient[colourIndex - 1] : Color.red; 
			Color endColour = colourGradient[colourIndex]; 
			float lerpValue = normalizedY - (float)colourIndex / (colourGradient.Length - 1);
			
			Color vertexColour = Color.Lerp(startColour, endColour, lerpValue);
			
			colours[i] = vertexColour; 
		}
	}
}
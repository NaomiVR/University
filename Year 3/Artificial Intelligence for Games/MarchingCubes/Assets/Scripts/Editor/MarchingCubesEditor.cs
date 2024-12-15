using UnityEditor;
using UnityEngine;

namespace Editor
{
    [CustomEditor(typeof(MarchingCubes))]
    public class MarchingCubesEditor : UnityEditor.Editor
    {
        private SerializedProperty _gridSizeX;
        private SerializedProperty _gridSizeY;
        private SerializedProperty _gridSizeZ;

        private SerializedProperty _isoValue;
        private SerializedProperty _noiseScale;
        private SerializedProperty _noiseAmplitude;

        private SerializedProperty _mesh;
        private SerializedProperty _meshFilter;
        private SerializedProperty _vertices;
        private SerializedProperty _triangles;
        private SerializedProperty _colours;

        private void OnEnable()
        {
            _gridSizeX = serializedObject.FindProperty("gridSizeX");
            _gridSizeY = serializedObject.FindProperty("gridSizeY");
            _gridSizeZ = serializedObject.FindProperty("gridSizeZ");
            
            _isoValue = serializedObject.FindProperty("isoValue");
            _noiseScale = serializedObject.FindProperty("noiseScale");
            _noiseAmplitude = serializedObject.FindProperty("noiseAmplitude");
            
            _mesh = serializedObject.FindProperty("mesh");
            _meshFilter = serializedObject.FindProperty("meshFilter");
            _vertices = serializedObject.FindProperty("vertices");
            _triangles = serializedObject.FindProperty("triangles");
            _colours = serializedObject.FindProperty("colours");
        }

        public override void OnInspectorGUI()
        {
            serializedObject.Update();
            
            EditorGUILayout.PropertyField(_gridSizeX);
            EditorGUILayout.PropertyField(_gridSizeY);
            EditorGUILayout.PropertyField(_gridSizeZ);
            
            EditorGUILayout.PropertyField(_isoValue);
            EditorGUILayout.PropertyField(_noiseScale);
            EditorGUILayout.PropertyField(_noiseAmplitude);
            
            EditorGUILayout.PropertyField(_mesh);
            EditorGUILayout.PropertyField(_meshFilter);
            EditorGUILayout.PropertyField(_vertices);
            EditorGUILayout.PropertyField(_triangles);
            EditorGUILayout.PropertyField(_colours);
            
            serializedObject.ApplyModifiedProperties();

            if (!Application.isPlaying)
            {
                Repaint();
            }
        }
    }
}

Plugin name: Procedural Generation Tool (ProcGenTool)

Creator: Luke Barnes

This is a tool created for the sole purpose of generating 3D procedural terrain directly into a Unreal Engine 5 level.

The key features of it include the following:
	- The ability to randomise every input variable
	- Terrain Generation using Perlin Noise
	- File saving of the custom generated terrain in a variety of formats including .CTM which was created for this plugin




Short Tutorial:

1. Create a fresh empty level, naming doesn't matter.
2. Open up the plugin interface under windows, ProcGen
3. Spawn a directional light and a TerrainMeshActor* using the buttons provided under Generator
4. Either choose to Randomise Variables or input each variable yourself**
5. Click on the Generate Terrain button***
6. If a variation of the mesh isn't to your liking there is a Clear Current TerrainMeshActor button that will reset the actor in the level allowing you to generate a new variation.
7. Once you have generated terrain that you like you are able to save it as a file of its raw data for future use****



*You can only have one TerrainMeshActor instance created at any given time in the editor

**The following variables have no current function, they are to be implemented fully in a later version: SeaLevel, Min and Max River Start Height

***Sometimes the terrain appears to look more like grass than actual land, I recommend that the Scale Factor be set around 0.008

****Only one file type, CTM, is available right now and it is a custom file type made for this plugin, FBX and OBJ will come in future versions.
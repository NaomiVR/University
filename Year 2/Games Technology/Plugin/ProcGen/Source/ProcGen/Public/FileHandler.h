#pragma once

class FFileHandler
{
public:
	FFileHandler() {};

	void DialogueContextCTM() const;
	void DialogueContextFBX() const;
	void DialogueContextOBJ() const;
	
	void CTMSave(const FString& FileName) const; // Custom Terrain Mesh
	void FBXSave() const;
	void OBJSave() const;

	void CTMLoad() const;
	void FBXLoad() const;
	void OBJLoad() const;
};

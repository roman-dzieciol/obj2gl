#include "StdAfx.h"
#include "ObjFile.h"

ObjFile::ObjFile(wstring FileName, TriMesh& mesh)
{
	ifstream file;

	// Open file
	file.open(FileName.c_str(), ios_base::in | ios_base::binary);
	if( !file )
		throw swException(wstring_make() << "Cannot open file: " << FileName);

	// Vector data
	vector<Vector3D> Verts; // xyzxyz...
	vector<Vector3D> TexVerts; // uvwuvw...
	vector<Vector3D> Normals; // xyzxyz...

	// command tokens
	static const string cmdMeshVert("v");
	static const string cmdNormal("vn");
	static const string cmdTexVert("vt");
	static const string cmdFaces("f");

	while( file.good() )
	{
		// read line
		string s;
		getline(file, s);
		if( s.empty() )
			continue;

		// read token name
		istringstream strstream(s);
		string cmd;
		strstream >> cmd;

		// read token data
		if( cmd == cmdMeshVert )
		{  
			Vector3D meshVert;
			strstream >> meshVert.x;
			strstream >> meshVert.y;
			strstream >> meshVert.z;
			Verts.push_back(meshVert);
			//cout << cmd << " " << meshVert[0] << " "<< meshVert[1] << " " << meshVert[2] << endl;
		}
		else if( cmd == cmdTexVert )
		{
			Vector3D texVert;
			strstream >> texVert.x;
			strstream >> texVert.y;
			strstream >> texVert.z;
			TexVerts.push_back(texVert);
		}
		else if( cmd == cmdNormal )
		{
			Vector3D normal;
			strstream >> normal.x;
			strstream >> normal.y;
			strstream >> normal.z;
			Normals.push_back(normal);
		}
		else if( cmd == cmdFaces )
		{
			int vertIdx[3];
			int texCoordIdx[3];
			int normalIdx[3];
			char separator;

			strstream >> vertIdx[0];
			strstream >> separator;
			strstream >> texCoordIdx[0];
			strstream >> separator;
			strstream >> normalIdx[0];

			strstream >> vertIdx[1];
			strstream >> separator;
			strstream >> texCoordIdx[1];
			strstream >> separator;
			strstream >> normalIdx[1];

			strstream >> vertIdx[2];
			strstream >> separator;
			strstream >> texCoordIdx[2];
			strstream >> separator;
			strstream >> normalIdx[2];

			Vert triverts[3];
			for( int i=0; i<3; ++i )
			{
				triverts[i].Point = Verts[vertIdx[i]-1];
				triverts[i].TexCoord = TexVerts[texCoordIdx[i]-1];
				triverts[i].Normal = Normals[normalIdx[i]-1];
			}
			
			mesh.Tris.push_back(Triangle(triverts[0], triverts[1], triverts[2]));
		}
	}
}
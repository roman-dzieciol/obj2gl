#include "StdAfx.h"
#include "GLFile.h"


enum GLFileModes
{
	GLFM_None
,	GLFM_InterleavedNonIndexed
,	GLFM_InterleavedIndexed
,	GLFM_Indexed
,	GLFM_NonIndexed
};


struct GLHeader 
{
	static const char* Magic;
	unsigned char Mode;
};

const char* GLHeader::Magic = "GLFL";

struct FloatBuffer : public vector<unsigned int> 
{
	void AddVector3D(Vector3D v)
	{ 
		AddFloat(v.x);
		AddFloat(v.y);
		AddFloat(v.z);
	}

	void AddVector2D(Vector3D v)
	{ 
		AddFloat(v.x);
		AddFloat(v.y);
	}

	void AddFloat(float f)
	{ 
		unsigned long l = *reinterpret_cast<unsigned int*>(&f);
		//push_back(_byteswap_ulong(l)); 
		push_back(l); // mac
	}

	void write( ofstream& file )
	{
		unsigned int BufferSize = size() * sizeof(at(0));
		//unsigned int BufferSizeBE = _byteswap_ulong(BufferSize);
		unsigned int BufferSizeBE = BufferSize; // mac
		file.write((char*)&BufferSizeBE, sizeof(BufferSizeBE));
		file.write((char*)&at(0), BufferSize);
	}
};

struct LEIndexBuffer : public vector<unsigned short> 
{
	void push_back_le(unsigned short l)
	{ 
		//push_back(_byteswap_ushort(l)); 
		push_back(l); // mac
	}

	void write( ofstream& file )
	{
		unsigned int BufferSize = size() * sizeof(at(0));
		//unsigned int BufferSizeBE = _byteswap_ulong(BufferSize);
		unsigned int BufferSizeBE = BufferSize; // mac
		file.write((char*)&BufferSizeBE, sizeof(BufferSizeBE));
		file.write((char*)&at(0), BufferSize);
	}
};



GLFile::GLFile(wstring FileName, TriMesh& mesh)
{
	ofstream file;

	// Open file
	file.open(FileName.c_str(), ios_base::out | ios_base::binary);
	if( !file )
		throw swException(wstring_make() << "Cannot open file: " << FileName);

	// Setup header
	GLHeader header;
	header.Mode = GLFM_NonIndexed;

	// Write header
	file << header.Magic;
	//unsigned long ModeBE = _byteswap_ulong(header.Mode);
	unsigned long ModeBE = header.Mode; // mac
	file.write((char*)&ModeBE, sizeof(ModeBE));

	switch(header.Mode)
	{
	case GLFM_NonIndexed:
		{
			FloatBuffer points;
			FloatBuffer texcoords;
			FloatBuffer normals;

			for( size_t i=0; i<mesh.Tris.size(); ++i )
			{
				for( int j=0; j<3; ++j )
				{
					points.AddVector3D(mesh.Tris[i].Verts[j].Point);
					normals.AddVector3D(mesh.Tris[i].Verts[j].Normal);

					// Invert y axis
					Vector3D texcoord(mesh.Tris[i].Verts[j].TexCoord);
					texcoords.AddVector2D(Vector3D(texcoord.x, 1.0f-texcoord.y, texcoord.z));
				}

				//cout << "F[" << i << "] " << mesh.Tris[i] << endl;
			}

			points.write(file);
			texcoords.write(file);
			normals.write(file);

			break;
		}

	case GLFM_Indexed:
		{
			// non-interleaved
			// GL_TRIANGLES
			// indexed

			//LEIndexBuffer index;
			//LEBuffer verts;
			//LEBuffer texverts;
			//LEBuffer normals;

			//
			// Index buffer
			//

			//assert( !(mesh.MeshTris.size() == mesh.TexTris.size() == mesh.NormalIdx.size()) );

			//// Index buffer
			//for( size_t i=0; i<mesh.MeshTris.size(); ++i )
			//	index.push_back_le(mesh.MeshTris[i]);

			//for( size_t i=0; i<mesh.MeshTris.size(); i+=3 )
			//	cout << "I " << (i/3) << " " << mesh.MeshTris[i] << " " << mesh.MeshTris[i+1] << " " << mesh.MeshTris[i+2] << endl;

			//// Vertex buffer
			//for( size_t i=0; i<mesh.Verts.size(); ++i )
			//	verts.push_back_le(mesh.Verts[i]);

			//for( size_t i=0; i<mesh.Verts.size(); i+=3 )
			//	cout << "V " << (i/3) << " " << mesh.Verts[i] << " " << mesh.Verts[i+1] << " " << mesh.Verts[i+2] << endl;


			//// TexCoord buffer
			//vector<float> texmap((mesh.Verts.size()/3)*2);
			//for( size_t i=0; i<mesh.MeshTris.size(); ++i )
			//{
			//	texmap[mesh.MeshTris[i]*2] = mesh.TexVerts[mesh.TexTris[i]];
			//	texmap[mesh.MeshTris[i]*2+1] = mesh.TexVerts[mesh.TexTris[i]+1];
			//}

			//for( size_t i=0; i<texmap.size(); ++i )
			//	texverts.push_back_le(texmap[i]);

			//for( size_t i=0; i<texmap.size(); i+=2 )
			//	cout << "T " << (i/2) << " " << texmap[i] << " " << texmap[i+1] << endl;

			//// Normals buffer
			//vector<float> normalmap(mesh.Verts.size());
			//for( size_t i=0; i<mesh.MeshTris.size(); ++i )
			//{
			//	int vidx = (mesh.MeshTris[i]) * 3;
			//	int tidx = (mesh.NormalIdx[i]) * 3;

			//	normalmap[vidx] = mesh.Normals[tidx];
			//	normalmap[vidx+1] = mesh.Normals[tidx+1];
			//	normalmap[vidx+2] = mesh.Normals[tidx+2];
			//}

			//for( size_t i=0; i<normalmap.size(); ++i )
			//	normals.push_back_le(normalmap[i]);

			//for( size_t i=0; i<normalmap.size(); i+=3 )
			//	cout << "N " << (i/3) << " " << normalmap[i] << " " << normalmap[i+1] << " " << normalmap[i+2] << endl;


			//index.write(file);
			//verts.write(file);
			//texverts.write(file);
			//normals.write(file);

			//for( size_t i=0; i<mesh.MeshTris.size(); i+=3 )
			//{
			//	cout << "F: " << (i/3) 
			//		<< " V: " << mesh.Verts[mesh.MeshTris[i]] << " " << mesh.Verts[mesh.MeshTris[i+1]] << " " << mesh.Verts[mesh.MeshTris[i+2]] 
			//	<< endl;
			//}

			break;
		}
	}

	
}
#pragma once

struct Vector3D
{
	float x,y,z;

	Vector3D(){}
	Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

	friend ostream& operator << (ostream& os, const Vector3D& v)
	{
		return os << v.x << ", " << v.y << ", " << v.z;
	}

};


struct Vert
{
	Vector3D Point;
	Vector3D TexCoord;
	Vector3D Normal;

	Vert(){}
	Vert(Vector3D Point, Vector3D TexCoord, Vector3D Normal) : Point(Point), TexCoord(TexCoord), Normal(Normal) {}


};

struct Triangle
{
	Vert Verts[3];

	Triangle(){}
	Triangle(Vert A, Vert B, Vert C)
	{
		Verts[0] = A;
		Verts[1] = B;
		Verts[2] = C;
	}

	friend ostream& operator << (ostream& os, const Triangle& t)
	{
		return os
			<< "V:(" << t.Verts[0].Point << ") (" << t.Verts[1].Point << ") (" << t.Verts[2].Point << ")"
			<< " T:(" << t.Verts[0].TexCoord << ") (" << t.Verts[1].TexCoord << ") (" << t.Verts[2].TexCoord << ")"
			<< " N:(" << t.Verts[0].Normal << ") (" << t.Verts[1].Normal << ") (" << t.Verts[2].Normal << ")";
	}
};



class TriMesh
{
public:
	TriMesh();

public:
	vector<Triangle> Tris;
};

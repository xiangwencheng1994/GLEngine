#version 330

in int	_meshId;
in int	_flag;
in mat4	_local;

struct MeshDesc
{
	float	aabbMinX;
	float	aabbMinY;
	float	aabbMinZ;
	float	aabbMaxX;
	float	aabbMaxY;
	float	aabbMaxZ;
	int		baseVertex;
	int		baseIndex;
	int		vertCount;
};

layout(shared, std140) uniform Meshes
{
	MeshDesc _meshes[256];
};

uniform mat4		_mvp;

out int vertCount;		 //indices count
out int primCount;       //instance count
out int firstIndex;      //first index offset
out int baseVertex;      //base vertex
out int baseInstance;    //base instance

bool isInVisible()
{
	//TODO: calc
	return false;
}

void main()
{
	baseInstance = gl_VertexID;
	//if((_flag & 0x1) == 0 || isInVisible())
	//{
	//	vertCount = 0;
	//	primCount = 0;
	//	firstIndex = 0;
	//	return;
	//}
	vertCount = _meshes[_meshId].vertCount;
	baseVertex = _meshes[_meshId].baseVertex;
	firstIndex = _meshes[_meshId].baseIndex;
	primCount = 1;
}
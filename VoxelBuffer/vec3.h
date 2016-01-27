#pragma once

/**
 * These were made just to keep the parameter lists of the VoxelBuffer functions from being really long.
 * 
 * CDB
 */
 
struct vec3 {
	float x;
	float y;
	float z;
};

struct ivec3 {
	int x;
	int y;
	int z;
};

struct voxel
{
	float density;
	float light;
};
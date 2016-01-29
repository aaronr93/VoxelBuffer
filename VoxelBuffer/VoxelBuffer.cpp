/*
VoxelBuffer.cpp
Aaron Rosenberger
COMP 361 Graphics
Due 1/29/16
*/

#include "VoxelBuffer.h"
#include <fstream>
#include <math.h>
using std::ifstream;
using std::string;
using std::atoi;
using std::atof;

VoxelBuffer::VoxelBuffer(float delta, const ivec3& dimensions)
{
	this->delta = delta;
	this->dimensions = dimensions;
}

VoxelBuffer::~VoxelBuffer(void)
{
	//delete[] voxels;
}

int VoxelBuffer::getVoxelIndex(const vec3& coords) const
{
	// width = dimensions.x
	// height = dimensions.y
	float x, y, z;
	x = floor(coords.x / delta);
	y = floor(coords.y / delta);
	z = floor(coords.z / delta);
	return (z * dimensions.x * dimensions.y) + (y * dimensions.x + x);
}

int VoxelBuffer::getDimensions(void) const
{
	return dimensions.x;
}

float VoxelBuffer::densityRead(const vec3& coords) const
{
	int index = getVoxelIndex(coords);
	return voxels[index].density;
}

float VoxelBuffer::lightRead(const vec3& coords) const
{
	//int index = getVoxelIndex(coords);
	//return voxels.at(index).density;

	// If we're skipping light for each voxel for this milestone, why waste computation time?
	return -1.0f;
}

void VoxelBuffer::densityWrite(const vec3& coords, float value)
{
	int index = getVoxelIndex(coords);
	voxels[index].density = value;
}

void VoxelBuffer::lightWrite(const vec3& coords, float value)
{
	int index = getVoxelIndex(coords);
	voxels[index].light = value;
}

vec3 VoxelBuffer::getVoxelCenter(const vec3& coords) const
{
	vec3 retval;
	retval.x = coords.x * delta + (delta / 2.0f);
	retval.y = coords.y * delta + (delta / 2.0f);
	retval.z = coords.z * delta + (delta / 2.0f);
	return retval;
}

vec3 VoxelBuffer::getVoxelCenter(const ivec3& coords) const
{
	vec3 retval;
	retval.x = coords.x * delta + (delta / 2.0f);
	retval.y = coords.y * delta + (delta / 2.0f);
	retval.z = coords.z * delta + (delta / 2.0f);
	return retval;
}

VoxelBuffer * VoxelBuffer::factory(const string& filename)
{
	ifstream fin(filename);
	string inputBuffer;
	VoxelBuffer * tempBuffer;

	fin >> inputBuffer;		// "DELT"
	fin >> inputBuffer;		// Delta value
	float delta = (float)atof(inputBuffer.c_str());

	fin >> inputBuffer;		// "XYZC"
	fin >> inputBuffer;
	ivec3 dimensions;
	dimensions.x = atoi(inputBuffer.c_str());
	fin >> inputBuffer;
	dimensions.y = atoi(inputBuffer.c_str());
	fin >> inputBuffer;
	dimensions.z = atoi(inputBuffer.c_str());

	tempBuffer = new VoxelBuffer(delta, dimensions);
	float tempDensity/*, tempLight*/;		// Omit reading in lights temporarily
	voxel tempVoxel;
	int voxelBufferSize = dimensions.x * dimensions.y * dimensions.z;
	tempBuffer->voxels = new voxel[voxelBufferSize];
	int i = 0;

	// Read in voxel densities (and lights...later)
	while (!fin.eof()) {
		fin >> inputBuffer;
		tempDensity = (float)atof(inputBuffer.c_str());
		tempVoxel.density = tempDensity;
		tempVoxel.light = -1.0;
		tempBuffer->voxels[i++] = tempVoxel;	// Add voxel to the 1D array
	}

	return tempBuffer;
}
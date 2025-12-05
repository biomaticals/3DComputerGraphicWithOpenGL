// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

class Skybox
{
public:
	Skybox();
	~Skybox();
	void draw();

private:
	typedef unsigned int uint;
	typedef const char* pcStr;
	uint textures[6];
	static uint _loadTexture(pcStr filename);
};
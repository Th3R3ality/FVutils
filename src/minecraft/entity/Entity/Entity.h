#pragma once
#include <jni.h>
#include "../../IClass.h"

struct Entity : public IClass
{
	const char* klassPath = "net.minecraft.entity.Entity";
};

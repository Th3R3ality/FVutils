#include "GlStateManager.h"

MAKE_INITIALISER( GlStateManager );

void GlStateManager::enablePolygonOffset()
{
	TLSENV->CallStaticVoidMethod(GlStateManager::klass, GlStateManager::methodIDs["enablePolygonOffset"]);
}

void GlStateManager::disablePolygonOffset()
{
	TLSENV->CallStaticVoidMethod(GlStateManager::klass, GlStateManager::methodIDs["disablePolygonOffset"]);
}

void GlStateManager::doPolygonOffset( jfloat factor, jfloat units )
{
	TLSENV->CallStaticVoidMethod(GlStateManager::klass, GlStateManager::methodIDs["doPolygonOffset"], factor, units);
}

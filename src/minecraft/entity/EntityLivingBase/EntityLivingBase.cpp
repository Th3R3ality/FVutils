#include "EntityLivingBase.h"

jfloat EntityLivingBase::getHealth()
{
    static jmethodID fieldId = java::env->GetMethodID(klass, "getHealth", "()F");

    return java::env->CallFloatMethod(instance, fieldId);
}

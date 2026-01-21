// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PORTFOLIOPROJECT_API ComponentTypeID
{
public:
    template <typename T>
    static int32 GetTypeID() {
        static const int32 TypeID = NextID();
        return TypeID;
    }

private:
    static int32 NextID() {
        static int32 Counter = 0;
        return Counter++;
    }
};

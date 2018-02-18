/**
*  @file    GPUCommand.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    13/02/2018
*  @version v1.0
*
*  @section System Module
*           Core State Manager.
*
*  @brief Contains all GPU information needed for GPU sheduling and management.
*
*  @section Description
*		  GPUCommand contains a set of D3D12 Data structures that are used for managing the GPU commands and calls.
*  
*/


#pragma once

#include "pch.h"

struct   GPUCommandObject 
{
	ID3D12CommandQueue*						gpu_command_queue = nullptr;
	ID3D12Fence*							gpu_fence = nullptr;
	UINT*									backbuffer_index = nullptr;
	Microsoft::WRL::Wrappers::Event*		fence_events = nullptr;
	UINT64*									fence_values = nullptr;
};
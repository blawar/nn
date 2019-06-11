#pragma once

#include "nn.h"

namespace nn
{
	typedef u32 Handle;
	typedef u32 Result;

	class Service
	{
	public:
		enum class Type
		{
			Uninitialized,
			Normal,
			Domain,
			DomainSubservice,
			Override
		};

		Handle handle;
		u32 object_id;
		Type type;
	};
}

#include "ipc.h"

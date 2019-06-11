#pragma once

#include "nn.h"

#define IPC_MAX_BUFFERS 8
#define IPC_MAX_OBJECTS 8

namespace nn
{
	class Ipc
	{
	public:
		enum class BufferType
		{
			Normal = 0,  ///< Regular buffer.
			Type1 = 1,   ///< Allows ProcessMemory and shared TransferMemory.
			Invalid = 2,
			Type3 = 3    ///< Same as Type1 except remote process is not allowed to use device-mapping.
		};

		enum class BufferDirection
		{
			Send = 0,
			Recv = 1,
			Exch = 2,
		};

		class Command
		{
		public:
			size_t NumSend;
			size_t NumRecv;
			size_t NumExch;
			const void* Buffers[IPC_MAX_BUFFERS];
			size_t BufferSizes[IPC_MAX_BUFFERS];
			BufferType BufferTypes[IPC_MAX_BUFFERS];

			size_t NumStaticIn;
			size_t NumStaticOut;
			const void* Statics[IPC_MAX_BUFFERS];
			size_t StaticSizes[IPC_MAX_BUFFERS];
			u8     StaticIndices[IPC_MAX_BUFFERS];

			bool   SendPid;
			size_t NumHandlesCopy;
			size_t NumHandlesMove;
			Handle Handles[IPC_MAX_OBJECTS];

			size_t NumObjectIds;
			u32    ObjectIds[IPC_MAX_OBJECTS];
		};

		class IRequestBase
		{
		public:
		protected:
			class Header
			{
			public:
			protected:
				u64 magic;
				u64 id;
			};
		};

		template<class A>
		class Request : public IRequest
		{
		public:
		protected:
			Header header;
			A a;
		};

		template<class A, class B>
		class Request : public IRequest
		{
		public:
		protected:
			Header header;
			A a;
			B b;
		};

		template<class A, class B, class C>
		class Request : public IRequest
		{
		public:
		protected:
			Header header;
			A a;
			B b;
			C c;
		};

		template<class A, class B, class C, class D
		class Request : public IRequest
		{
		public:
		protected:
			Header header;
			A a;
			B b;
			C c;
			D d;
		};

		class Response
		{
		public:
		};

		class Response
		{
		public:
		};

		const Command& command() const { return m_command; }
		Command& command() { return m_command; }

	protected:
		Command m_command;
	};
}
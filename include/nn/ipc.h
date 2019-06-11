#pragma once

#include "nn.h"

#define IPC_MAX_BUFFERS 8
#define IPC_MAX_OBJECTS 8

#define SFCI_MAGIC 0x49434653
#define SFCO_MAGIC 0x4f434653

namespace nn
{
	class Response
	{
	public:
		Result result()
		{
			return m_result;
		}
	protected:
		u64 m_magic;
		u64 m_result;
	};

	template<class A>
	class ResponseV : public Response
	{
	public:
		Result result(A* a)
		{
			*a = this->a;
			return m_result;
		}
	protected:
		A a;
	};

	template<u64 ID, class R>
	class Request
	{
	public:
		Request() : id(ID), magic(SFCI_MAGIC)
		{
		}

		R send(const Service& service)
		{
			R response;
			return response;
		}

		u64 magic;
		u64 id;
	};

	template<u64 ID, class R, class A, class B, class C, class D>
	class RequestVVVV : public Request<ID, R>
	{
	public:
		A a;
		B b;
		C c;
		D d;
	};

	template<u64 ID, class R, class A, class B, class C>
	class RequestVVV : public Request<ID, R>
	{
	public:
		A a;
		B b;
		C c;
	};

	template<u64 ID, class R, class A, class B>
	class RequestVV : public Request<ID, R>
	{
	public:
		RequestVV(const A& a, const B& b) : Request(), a(a), b(b)
		{
		}

		A a;
		B b;
	};

	template<u64 ID, class R, class A>
	class RequestV : public Request<ID, R>
	{
	public:
		RequestV(const A& a) : Request(), a(a)
		{
		}

		A a;
	};

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

		const Command& command() const { return m_command; }
		Command& command() { return m_command; }

	protected:
		Command m_command;
	};
}
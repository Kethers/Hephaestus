#pragma once

#include "Hephaestus/Core/Base.h"
#include "Hephaestus/Core/Log.h"

namespace Hep
{
	struct Buffer
	{
		byte* Data;
		uint32_t Size;

		Buffer()
			: Data(nullptr), Size(0)
		{}

		Buffer(void* data, uint32_t size)
			: Data((byte*)data), Size(size)
		{}

		static Buffer Copy(const void* data, uint32_t size)
		{
			Buffer buffer;
			buffer.Allocate(size);
			memcpy(buffer.Data, data, size);
			return buffer;
		}

		void Allocate(uint32_t size)
		{
			delete[] Data;
			Data = nullptr;

			if (size == 0)
				return;

			Data = new byte[size];
			Size = size;
		}

		void Release()
		{
			delete[] Data;
			Data = nullptr;
			Size = 0;
		}

		void ZeroInitialize()
		{
			if (Data)
				memset(Data, 0, Size);
		}

		template <typename T>
		T& Read(uint32_t offset = 0)
		{
			return *(T*)(Data + offset);
		}

		byte* ReadBytes(uint32_t size, uint32_t offset)
		{
			HEP_CORE_ASSERT(offset + size <= Size, "Buffer overflow!");
			byte* buffer = new byte[size];
			memcpy(buffer, Data + offset, size);
			return buffer;
		}

		void Write(void* data, uint32_t size, uint32_t offset = 0)
		{
			HEP_CORE_ASSERT(offset + size <= Size, "Buffer overflow!");
			memcpy(Data + offset, data, size);
		}

		operator bool() const
		{
			return Data;
		}

		byte& operator[](int index)
		{
			return Data[index];
		}

		byte operator[](int index) const
		{
			return Data[index];
		}

		template <typename T>
		T* As()
		{
			return (T*)Data;
		}

		uint32_t GetSize() const { return Size; }
	};
}

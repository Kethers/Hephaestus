﻿#pragma once

#include "Hephaestus/Core/Base.h"

namespace Hep
{
	struct Buffer
	{
		byte* Data;
		uint32_t Size;

		Buffer()
			: Data(nullptr), Size(0)
		{ }

		Buffer(byte* data, uint32_t size)
			: Data(data), Size(size)
		{ }

		static Buffer Copy(void* data, uint32_t size)
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

		void ZeroInitialize()
		{
			if (Data)
				memset(Data, 0, Size);
		}

		void Write(byte* data, uint32_t size, uint32_t offset = 0)
		{
			HEP_CORE_ASSERT(offset + size <= Size, "Buffer overflow!");
			memcpy(Data + offset, data, size);
		}

		operator bool() const
		{
			return Data;
		}

		byte& operator[](const uint32_t index)
		{
			return Data[index];
		}

		byte operator[](const uint32_t index) const
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
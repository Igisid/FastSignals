#include "../include/function_detail.h"
#include <cstddef>
#include <functional>

namespace is::signals::detail
{

packed_function::packed_function(packed_function&& other) noexcept
{
	m_isBufferAllocated = other.m_isBufferAllocated;
	m_proxy = other.m_proxy ? other.m_proxy->move(&m_buffer) : nullptr;
	other.m_proxy = nullptr;
}

packed_function::packed_function(const packed_function& other)
{
	m_isBufferAllocated = other.m_isBufferAllocated;
	m_proxy = other.m_proxy ? other.m_proxy->clone(&m_buffer) : nullptr;
}

packed_function& packed_function::operator=(packed_function&& other) noexcept
{
	reset();
	m_isBufferAllocated = other.m_isBufferAllocated;
	m_proxy = other.m_proxy ? other.m_proxy->move(&m_buffer) : nullptr;
	other.m_proxy = nullptr;
	return *this;
}

packed_function& packed_function::operator=(const packed_function& other)
{
	auto* proxy = other.m_proxy ? other.m_proxy->clone(&m_buffer) : nullptr;
	bool isBufferAllocated = other.m_isBufferAllocated;
	reset();
	m_proxy = proxy;
	m_isBufferAllocated = isBufferAllocated;
	return *this;
}

packed_function::~packed_function() noexcept
{
	reset();
}

void packed_function::reset() noexcept
{
	if (m_proxy != nullptr)
	{
		if (m_isBufferAllocated)
		{
			m_proxy->~base_function_proxy();
		}
		else
		{
			delete m_proxy;
		}
		m_proxy = nullptr;
	}
}

base_function_proxy& packed_function::unwrap() const
{
	if (m_proxy == nullptr)
	{
		throw std::bad_function_call();
	}
	return *m_proxy;
}

} // namespace is::signals::detail

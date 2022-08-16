#include<iostream>

enum{bit_count = 8*sizeof(size_t) };

class vector_bool {
public:
	vector_bool();
	vector_bool(const vector_bool&);
	vector_bool(vector_bool&&);
	vector_bool(std::initializer_list<bool>);
	vector_bool(size_t);
	vector_bool(size_t, bool);
	~vector_bool();
	void insert(size_t pos, bool val)
	{
		if (this->m_buf==NULL)
		{
			m_cap = bit_count;
			m_buf = new size_t[1];
			m_buf[m_size++] = val;
			return;
		}
		if (m_size == m_cap)
		{
			m_cap += bit_count;
			size_t* ptr = new size_t[m_cap / bit_count];
			for(int i = 0; i < (m_size / bit_count); i++)
			{
				ptr[i] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = ptr;
			ptr = nullptr;
		}
		for (int i = m_size; i > pos; i--)
		{
			(*this)[i]=(*this)[i-1];
		}
			(*this)[pos] = val;
			++m_size;
	}
	void erase(size_t pos)
	{
		if (this->m_buf == NULL)
		{
			return;
		}
		for (size_t i = 0; i > pos; i--)
		{
			(*this)[i - 1] = (*this)[i];
		}
		--m_size;
	}
	void push_back(bool val)
	{
		if (this->m_buf == NULL)
		{
			m_cap = bit_count;
			m_buf = new size_t[1];
			(*this)[m_size++] = val;
			return;
		}
		if (m_size == m_cap)
		{
			m_cap += bit_count;
			size_t* ptr = new size_t[m_cap / bit_count];
			for (int i = 0; i < (m_size / bit_count); i++)
			{
				ptr[i] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = ptr;
			ptr = nullptr;
		}
	}
	class referance
	{
	public:
		referance(size_t*,size_t);
		referance(const referance&);
		referance(referance&&);
		referance& operator=(const referance&);
		referance&& operator=(referance&&);
		referance& operator=(bool val);
		operator bool() const;
		void flip();

	private:
		size_t* ptr;
		size_t  index;
		bool val; 
	};
	referance operator[](size_t pos)
	{
		return referance(m_buf, pos);
	}

private:
	size_t m_cap;
	size_t m_size;
	size_t* m_buf;
};

vector_bool::referance::referance(size_t* pt, size_t ind) :ptr{ pt }, index{ ind }, val{}
{
	val = ptr[index / bit_count] & (1 << (index % bit_count));
} 
void vector_bool::referance::flip()
{
		ptr[index / bit_count] ^= (1 << (index % bit_count));
		val != val;
}
vector_bool::referance::referance(const vector_bool::referance& oth) :ptr{oth.ptr}, index{oth.index},val{oth.val}
{
	
}
vector_bool::referance::referance(vector_bool::referance&& oth) :ptr{ oth.ptr }, index{ oth.index }, val{ oth.val }
{

}
vector_bool::referance& vector_bool::referance::operator=(const vector_bool::referance& oth)
{
	if (val != oth.val)
	{
		this->flip();
	}
	return *this;
}

vector_bool::referance&& vector_bool::referance::operator=(vector_bool::referance&& oth)
{
	if (val != oth.val)
	{
		this->flip();
	}
}

vector_bool::referance& vector_bool::referance::operator=(bool val)
{
	if (this->val != val)
	{
		this->flip();
	}
	return *this;
}

vector_bool::referance::operator bool() const
{
	return val;
}

vector_bool::vector_bool() : m_size{}, m_buf{}, m_cap{}
{

}

vector_bool::vector_bool(const vector_bool& oth) : m_cap{oth.m_cap} , m_size{oth.m_size}
{
	m_buf = new size_t[m_cap / bit_count];
	for (int i = 0; i < m_cap / bit_count; i++)
	{
		m_buf[i] = oth.m_buf[i];
	}
}

vector_bool::vector_bool(vector_bool&& oth)
{
	this->m_cap = oth.m_cap;
	this->m_buf = oth.m_buf;
	this->m_size = oth.m_size;
}

vector_bool::vector_bool(std::initializer_list<bool> init) : m_cap{}, m_size{init.size()},m_buf{}
{
	if (init.size())
	{
		while (m_cap < init.size())
		{
			m_cap += bit_count;
		}
		m_buf = new size_t[m_cap / bit_count];
		size_t bit = 1;
		int i = 0;
		for (auto it = init.begin(); it != init.end(); ++it,++i)
		{
			m_buf[i / bit_count] != (1 << (i % bit_count));
		}
		bit <<= 1;
	}
}

vector_bool::vector_bool(size_t count) : m_cap{},m_size{count},m_buf{}
{
	if (count)
	{
		while (m_cap < count)
		{
			m_cap += bit_count;
		}
		m_buf = new size_t[m_cap / bit_count];
	}
}

vector_bool::vector_bool(size_t count, bool val) : m_cap{}, m_size{ count }, m_buf{}
{
	if (count)
	{
		while (m_cap < count)
		{
			m_cap += bit_count;
		}
		m_buf = new size_t[m_cap / bit_count];
		if(val)
		{
			size_t bit = 1;
			for (int i = 0; i < m_size; i++)
			{
				m_buf[i / bit_count] |= bit;
				bit <<= 1;
			}
		}
	}
}

vector_bool::~vector_bool()
{
	if (m_buf != NULL)
	{
		delete[] m_buf;
	}
}

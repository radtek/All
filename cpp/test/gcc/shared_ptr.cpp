#include<iostream>
#include<memory>
using namespace std;
class CB;
class CA
{
public:
	CA():m_num(0)
	{
	}
	
	~CA()
	{
		cout << "CA's destruction" << endl;
	}
	
	void set_ptr(shared_ptr<CB> &ptr)
	{
		m_ptr = ptr;
	}
	
	void print_count()
	{
		cout << "CA's m_ptr count :"<< m_ptr.use_count() << endl;
	}

	void print_content()
	{
		cout << "CA's m_num :"<< m_num << endl;
	}

private:
	int m_num;
	shared_ptr<CB> m_ptr;
};


class CB
{
public:
	CB():m_num(0)
	{
	}
	
	~CB()
	{
		cout << "CB's destruction" << endl;
	}
	
	void set_ptr(shared_ptr<CA> &ptr)
	{
		m_ptr = ptr;
	}
	
	void print_count()
	{
		cout << "CB's m_ptr count :"<< m_ptr.use_count() << endl;
	}

	void print_content()
	{
		cout << "CB's m_num :"<< m_num << endl;
	}

private:
	int m_num;
	weak_ptr<CA> m_ptr;
};

int main()
{
	shared_ptr<CA> ptr_a(new CA());
	shared_ptr<CB> ptr_b(new CB());
	
	ptr_a->print_count();
	ptr_b->print_count();
	ptr_a->set_ptr(ptr_b);
	ptr_b->set_ptr(ptr_a);
	ptr_a->print_count();
	ptr_b->print_count();
	ptr_a->print_content();
	return 0;
}
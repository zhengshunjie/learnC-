#pragma once

//class Widget
//{
//public:
//	Widget(int size);
//	Widget(const Widget& rhs);
//	~Widget();
//
//	Widget& operator=(const Widget& rhs);
//
//	void doThis();
//	int showThat() const;
//
//private:
//	char* somePtr;
//
//	int refCount;
//};
//
//class RCWidget
//{
//public:
//	RCWidget(int size) : value(new Widget(size)) {};
//
//	void doThis() { value->doThis(); }
//
//	int showThat() const { return value->showThat(); }
//private:
//	Widget* value;
//};
class RCObject
{
public:
	void addReference() { ++refCount; }
	void removeReference() { if (--refCount == 0) delete this; }

	void markUnshareable() { shareable = false; }
	bool isShareable()const { return shareable; }

	bool isShared() const { return refCount > 1; }

protected:
	RCObject() : refCount(0), shareable(true) {}
	RCObject(const RCObject& rhs) : refCount(0), shareable(true) {}
	RCObject& operator=(const RCObject& rhs) { return *this; }
	virtual ~RCObject() {}
private:
	int refCount;
	bool shareable;
};

class BigInt : public RCObject
{
public:
	BigInt() : digits(0), ndigits(0), size(0) {};
	BigInt(unsigned u);
	BigInt(const char* s);
	~BigInt();

	BigInt& operator=(const BigInt& rhs);
private:
	char* digits;
	unsigned ndigits;
	unsigned size;
};

template <class T>
class RCPtr
{
public:
	RCPtr(T* realPtr = 0) :pointee(realPtr) { init(); }
	RCPtr(const RCPtr& rhs) :pointee(rhs.pointee) { init(); }
	~RCPtr() { if (pointee) pointee->removeReference(); }

	RCPtr& operator=(const RCPtr& rhs);
	T* operator->()const {return pointee; }
	T& operator*() const { return *pointee; }

private:
	T* pointee;
	void init();
};

template<class T>
void RCPtr<T>::init()
{
	if (0 == pointee)
		return;
	if (false == pointee->isShareable())
	{
		pointee = new T(*pointee);
	}
	pointee->addReference();
}

template<class T>
inline RCPtr<T>& RCPtr<T>::operator=(const RCPtr<T>& rhs)
{
	if (pointee != rhs.pointee)
	{
		if (pointee) pointee->removeReference();
		pointee = rhs.pointee;
		init();
	}

	return *this;
}

class RCBigInt
{
	friend RCBigInt operator+(const RCBigInt&, const RCBigInt&);
public:
	RCBigInt(const char* p) : value(new BigInt(p)) {}
	RCBigInt(unsigned u = 0) : value(new BigInt(u)) {}
	RCBigInt(const BigInt& bi) : value(new BigInt(bi)) {}
private:
	RCPtr<BigInt> value;
};

inline RCBigInt operator+(const RCBigInt& left, const RCBigInt& right)
{
	return RCBigInt(*(left.value) + *(right.value));
}
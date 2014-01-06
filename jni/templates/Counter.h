#ifndef COUNTER_H_
#define COUNTER_H_

template<class T>
class Counter{
private:
	static int count;
	int index;
public:
	static inline int getCount(){
		return count;
	}

	Counter<T>(){
		index = count;
		++count;
	};

	virtual ~Counter<T>(){
		--count;
	}

	inline int getIndex() const{
		return index;
	}

	inline bool isFirst() const{
		return index == 0;
	}

	inline bool isLast() const{
		return count == 1;
	}
};

template<class T>
int Counter<T>::count = 0;


#endif /* COUNTER_H_ */

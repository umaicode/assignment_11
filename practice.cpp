/*
* 객체들의 Set을 포함하는 테이블의 배열을 갖는 클래스 구현하기- template 버젼 완성하기
* 상속 관계 : Person <- Employee
* 상속 관계 : Student <- Workstudent
*/
#include <iostream>
#include <string>
#define DefaultSize 50
using namespace std;

class Exception {
public:
	virtual void Print() = 0;
};

class FullAddException : public Exception {
public:
	void Print() {
		cout << "가득 찼습니다~" << endl;
	}
};

class EmptyDeleteException : public Exception {
public:
	void Print() {
		cout << "지울게 더이상 없습니다~" << endl;
	}
};

class EmptySearchException : public Exception {
public:
	void Print() {
		cout << "찾을게 더이상 없습니다~" << endl;
	}
};

class EmptyPrintException : public Exception {
public:
	void Print() {
		cout << "프린트할게 더이상 없습니다." << endl;
	}
};

class Employee;
class Person {
protected:
	string pid;
	string pname;
public:
	Person() {}
	Person(string pid, string pname) : pid(pid), pname(pname) { }
	virtual ~Person() {}
	string GetName() { return pname; }
	void SetName(char* str) { pname = str; }
	virtual void Print() = 0;
	virtual bool Equals(Person* p);
};

bool Person::Equals(Person* p) {
	return pid == p->pid && pname == p->pname;
}

class Employee : public Person {
private:
	string eno;
	string role;
public:
	Employee() : Person() {}
	Employee(string pid, string pname, string eno, string role) : Person(pid, pname), eno(eno), role(role) { }
	virtual ~Employee() {}
	virtual void Print();
	virtual bool Equals(Employee* p);
};

bool Employee::Equals(Employee* p) {
	return pid == p->pid && pname == p->pname && eno == p->eno && role == p->role;
}

void Employee::Print() {
	cout << pid << ", " << pname << ", " << eno << ", " << role;
}

class Student {
protected:
	string sid;
	string major;
public:
	Student() {}
	Student(string sid, string major) : sid(sid), major(major) { }
	virtual ~Student() {};
	void Print();
};

void Student::Print() {
	cout << sid << ", " << major << ", ";
}

class WorkStudent : public Student {
private:
	string job;
public:
	WorkStudent() : Student() {}
	WorkStudent(string sid, string major, string job) : Student(sid, major), job(job) { }
	virtual ~WorkStudent() {}
	void Print();
	virtual bool Equals(WorkStudent* ws);
	string GetName() { return job; }
	void SetName(char* str) { job = str; }
};

void WorkStudent::Print() {
	Student::Print();
	cout << job;
}

bool WorkStudent::Equals(WorkStudent* ws) {
	return sid == ws->sid && major == ws->major && job == ws->job;
}


template <class T>
// function 들도 다 template 버전으로 만들어야 한다.
class Bag {
public:
	virtual int Add(T*); // 정수 하나를 bag에 삽입
	virtual int Delete(char*); //bag에서 정수 하나를 삭제
	virtual T* Search(char*);
	bool IsFull();
	// bag이 포화상태이면 true, 그렇지 않으면 false를 반환
	bool IsEmpty();
	// bag이 공백 상태이면 true, 그렇지 않으면 false를 반환
	int Top();
	virtual void Print();

protected:
	Bag(int bagSize);
	void Full(); // bag이 포화상태일 때의 조치
	void Empty(); // bag이 공백 상태일 때의 조치

	T** arr; //> 생성자에서 arr = new T*[Size]; > arr[i] = new T();
	int bagMaxSize; // 배열의 크기
	int topBag; // 배열에서 원소가 들어 있는 가장 높은 위치
	//*
	~Bag() {
		for (int i = 0; i < bagMaxSize; i++) {
			delete arr[i];
		}
		delete[] arr;
	}
	// */
};

template <class T>
Bag<T>::Bag(int bagSize) : bagMaxSize(bagSize) {
	topBag = 0;
	arr = new T * [bagSize];
}

template <class T>
void Bag<T>::Print() {
	T* p;
	for (int i = 0; i < topBag; i++) {
		p = arr[i];
		p->Print();
		cout << " | ";
	}
}

template <class T>
bool Bag<T>::IsFull() {
	if (topBag == bagMaxSize) {
		return true;
	}
	else {
		return false;
	}
}

template <class T>
bool Bag<T>::IsEmpty() {
	if (topBag == 0) {
		return true;
	}
	else {
		return false;
	}
}

template <class T>
void Bag<T>::Full() {
	cout << "Data Structure is FULL!!!" << endl;
}

template <class T>
void Bag<T>::Empty() {
	cout << "Data Structure is EMPTY!!!" << endl;
}


template <class T>
int Bag<T>::Add(T* x) {
	if (IsFull()) {
		Full();
		return -1;
	}

	if (topBag < bagMaxSize) {
		arr[topBag++] = x;
		return 1;
	}

	return -1;
}

template <class T>
int Bag<T>::Delete(char* str) {
	for (int i = 0; i < topBag; i++) {
		if (arr[i]->GetName() == str) {
			arr[i]->SetName("*******");
			return 1;
		}
	}
	return 0;
}

template <class T>
int Bag<T>::Top() {
	return topBag;
}

template <class T>
T* Bag<T>::Search(char* str) {
	for (int i = 0; i < topBag; i++) {
		if (strcmp(arr[i]->GetName().c_str(), str) == 0) {
			return arr[i];
		}
	}
	return nullptr;
}

template <class T>
class Set : public Bag<T> {
public:
	Set(int setSize) :Bag<T>(setSize) {}
	int Add(T*);
	int Delete(char*);
	void Print();
	T* Search(char*);
};

template <class T>
int Set<T>::Add(T* p) {
	if (IsFull()) {
		Full();
		return -1;
	}
	else {
		for (int i = 0; i < topBag; i++) {
			if ((*(arr[i])).Equals(p)) {
				cout << "중복된 값입니다." << endl;
				return -1;
			}
		}
		Bag<T>::Add(p);
		return 0;
	}
}

template <class T>
int Set<T>::Delete(char* str) {
	return Bag<T>::Delete(str);
}

template <class T>
void Set<T>::Print() {
	for (int i = 0; i < topBag; i++) {
		arr[i]->Print();
		if (i < topBag - 1) {
			cout << " | ";
		}
	}
	if (topBag > 0 && topBag % 5 != 0) {
		cout << " | ";
	}
}

template <class T>
T* Set<T>::Search(char* str) {
	return Bag<T>::Search(str);
}


template <class T>
class RecordSet : public Set<T> {
	int setMaxSize;//5개의 레코드 수
	int topRecordSet;//해당 레코드세트에서 입력할 위치
public:
	RecordSet(int maxSize) :Set<T>(maxSize), setMaxSize(maxSize) {
		topRecordSet = 0;
	}
	T* Search(char*);
	void Print();
	int Add(T* p);
};

template <class T>
T* RecordSet<T>::Search(char* str) {
	return Set<T>::Search(str);
}

template <class T>
void RecordSet<T>::Print() {
	Set<T>::Print();
	if (topRecordSet > 0 && topRecordSet % 5 != 0) {
		cout << " | ";
	}
}

template <class T>
int RecordSet<T>::Add(T* p) {
	if (topRecordSet < setMaxSize) {
		if (Set<T>::Add(p) != -1) {
			topRecordSet++;
			if (topRecordSet == setMaxSize) {
				cout << "가득 찼습니다." << endl;
				return 1; // 행이 증가함을 알리기 위해 1을 반환
			}
			return 0;
		}
	}

	if (topRecordSet + 1 < setMaxSize) {
		topRecordSet++;
		Set<T>::Add(p);
		return 0;
	}

	return -1; // 모든 열이 가득 찬 경우
}



// RecordTable은 Person이나 Student 의 상속을 받지 않는다. 
// -> 이것을 template로 만들지 않으면 RecordSet이 template로 되어있기 때문에 작동하지 않는다. 다른 객체들을 넣을 때 문제가 발생한다. 그렇기 때문에 template로 만들어야 한다.
template <class T>
class RecordTable {
	int tableMaxSize;
	int topRecordTable;
	// RecordSet** data;
	//------------------------------------ 교수님 코드 ------------------------------------//
	RecordSet<T>** data;
	//------------------------------------ 교수님 코드 ------------------------------------//
	int capacity;
public:
	RecordTable(int numberSet, int numberRecords) :tableMaxSize(numberSet), capacity(numberRecords) {
		topRecordTable = 0;
		data = new RecordSet<T> *[numberSet];//10개의 set
		for (int i = 0; i < numberSet; i++) {
			data[i] = new RecordSet<T>(numberRecords);//각 set는 5개 records
		}
	}

	int Add(T*); // 정수 하나를 bag에 삽입
	int Delete(char*);
	T* Search(char*);
	void Print();
};

template <class T>
int RecordTable<T>::Add(T* p) {
	int result = data[topRecordTable]->Add(p); // RecordSet의 Add() 메소드 호출 결과 저장
	if (result == 1) { // 행이 증가했을 경우
		topRecordTable++; // topRecordTable 변수를 증가시킴
		if (topRecordTable == tableMaxSize) {
			cout << "테이블이 가득 찼습니다." << endl;
			// return 1; // 테이블이 가득 찼음을 알리기 위해 1을 반환
			throw FullAddException();
		}
	}
	return 0;
}

template <class T>
int RecordTable<T>::Delete(char* str) {
	int deletedCount = 0;

	for (int i = 0; i < tableMaxSize; i++) {
		if (data[i]->Delete(str) == 1) {
			deletedCount++;
		}
	}

	if (deletedCount == 0) {
		throw EmptyDeleteException();
	}
	return deletedCount;
}//bag에서 정수 하나를 삭제

template <class T>
T* RecordTable<T>::Search(char* str) {
	for (int i = 0; i < tableMaxSize; i++) {
		T* result = data[i]->Search(str);
		if (result != nullptr) {
			return result; // 레코드를 성공적으로 찾은 경우
		}
	}

	throw EmptySearchException();
	// return nullptr; // 찾을 레코드가 없는 경우
}

template <class T>
void RecordTable<T>::Print() {
	if (topRecordTable == 0) {
		throw EmptyPrintException();
	}

	for (int i = 0; i < topRecordTable; i++) {
		data[i]->Print();
		if (i < topRecordTable) {
			cout << " | " << endl;
		}
	}
}

int main() {
	Person* members[30];
	WorkStudent* workers[20];
	RecordTable<Employee> etable(1, 5);
	RecordTable<WorkStudent> wtable(10, 5);
	int select;
	Employee* e;
	WorkStudent* ws;
	int result;
	while (1)
	{
		cout << "\n선택 1: member  객체 30개 입력, 2.table 출력, 3: table 객체 찾기,4. table에서 객체 삭제, 5. 종료" << endl;
		cin >> select;
		switch (select) {
		case 1://table에 객체 30개 입력
			try {
				members[0] = new Employee("p1", "hong", "E1", "Coding");
				members[1] = new Employee("p2", "hee", "E2", "Coding");
				members[2] = new Employee("p3", "kim", "E3", "Test");
				members[3] = new Employee("p4", "lee", "E4", "Test");
				members[4] = new Employee("p5", "ko", "E5", "Design");
				members[5] = new Employee("p6", "choi", "E6", "Design");
				members[6] = new Employee("p7", "han", "E7", "Sales");
				members[7] = new Employee("p8", "na", "E8", "Sales");
				members[8] = new Employee("p9", "you", "E9", "Account");
				members[9] = new Employee("p10", "song", "E10", "Production");
				workers[0] = new WorkStudent("s011", "coding", "hong");
				workers[1] = new WorkStudent("s012", "coding", "ong");
				workers[2] = new WorkStudent("s013", "coding", "dong");
				workers[3] = new WorkStudent("s014", "coding", "fong");
				workers[4] = new WorkStudent("s015", "coding", "tong");
				workers[5] = new WorkStudent("s016", "coding", "nong");
				workers[6] = new WorkStudent("s017", "coding", "mong");
				workers[7] = new WorkStudent("s018", "coding", "kong");
				workers[8] = new WorkStudent("s019", "coding", "long");
				workers[9] = new WorkStudent("s020", "coding", "pong");
				workers[10] = new WorkStudent("s021", "coding", "lim");
				workers[11] = new WorkStudent("s022", "coding", "mim");
				workers[12] = new WorkStudent("s023", "coding", "bim");
				workers[13] = new WorkStudent("s024", "coding", "dim");
				workers[14] = new WorkStudent("s025", "coding", "rim");
				workers[15] = new WorkStudent("s026", "coding", "qim");
				workers[16] = new WorkStudent("s021", "coding", "fim");
				workers[17] = new WorkStudent("s021", "coding", "him");
				workers[18] = new WorkStudent("s027", "coding", "jim");
				workers[19] = new WorkStudent("s027", "coding", "jjj");

				for (int i = 0; i < 10; i++) {
					etable.Add(dynamic_cast<Employee*>(members[i]));
				}

				for (int i = 0; i < 20; i++) {
					wtable.Add(workers[i]);
				}
			}
			catch (Exception& error) {
				error.Print();
			}

			break;
		case 2:
			// table의 모든 객체 출력하기
			try {
				etable.Print();
				wtable.Print();
			}
			catch (Exception& error) {
				error.Print();
			}

			break;
		case 3:
			// table에서 객체 찾기
			try {
				e = etable.Search("kim");
				if (e == nullptr)
					cout << "kim이 존재하지 않는다" << endl;
				else
					e->Print();
				cout << endl;

				ws = wtable.Search("kim");
				if (ws == nullptr)
					cout << "kim이 존재하지 않는다" << endl;
				else
					ws->Print();
			}
			catch (Exception& error) {
				error.Print();
			}

			break;
		case 4:
			// table에서 객체 삭제하기
			try {
				result = etable.Delete("hong");
				if (result > 0)
					cout << "삭제된 records 숫자" << result << endl;

				result = wtable.Delete("hong");
				if (result > 0)
					cout << "삭제된 records 숫자" << result << endl;
			}
			catch (Exception& error) {
				error.Print();
			}

			break;
		default:
			exit(0);
		}
	}

	system("pause");
	return 1;
}

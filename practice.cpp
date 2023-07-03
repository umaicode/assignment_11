/*
* ��ü���� Set�� �����ϴ� ���̺��� �迭�� ���� Ŭ���� �����ϱ�- template ���� �ϼ��ϱ�
* ��� ���� : Person <- Employee
* ��� ���� : Student <- Workstudent
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
		cout << "���� á���ϴ�~" << endl;
	}
};

class EmptyDeleteException : public Exception {
public:
	void Print() {
		cout << "����� ���̻� �����ϴ�~" << endl;
	}
};

class EmptySearchException : public Exception {
public:
	void Print() {
		cout << "ã���� ���̻� �����ϴ�~" << endl;
	}
};

class EmptyPrintException : public Exception {
public:
	void Print() {
		cout << "����Ʈ�Ұ� ���̻� �����ϴ�." << endl;
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
// function �鵵 �� template �������� ������ �Ѵ�.
class Bag {
public:
	virtual int Add(T*); // ���� �ϳ��� bag�� ����
	virtual int Delete(char*); //bag���� ���� �ϳ��� ����
	virtual T* Search(char*);
	bool IsFull();
	// bag�� ��ȭ�����̸� true, �׷��� ������ false�� ��ȯ
	bool IsEmpty();
	// bag�� ���� �����̸� true, �׷��� ������ false�� ��ȯ
	int Top();
	virtual void Print();

protected:
	Bag(int bagSize);
	void Full(); // bag�� ��ȭ������ ���� ��ġ
	void Empty(); // bag�� ���� ������ ���� ��ġ

	T** arr; //> �����ڿ��� arr = new T*[Size]; > arr[i] = new T();
	int bagMaxSize; // �迭�� ũ��
	int topBag; // �迭���� ���Ұ� ��� �ִ� ���� ���� ��ġ
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
				cout << "�ߺ��� ���Դϴ�." << endl;
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
	int setMaxSize;//5���� ���ڵ� ��
	int topRecordSet;//�ش� ���ڵ弼Ʈ���� �Է��� ��ġ
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
				cout << "���� á���ϴ�." << endl;
				return 1; // ���� �������� �˸��� ���� 1�� ��ȯ
			}
			return 0;
		}
	}

	if (topRecordSet + 1 < setMaxSize) {
		topRecordSet++;
		Set<T>::Add(p);
		return 0;
	}

	return -1; // ��� ���� ���� �� ���
}



// RecordTable�� Person�̳� Student �� ����� ���� �ʴ´�. 
// -> �̰��� template�� ������ ������ RecordSet�� template�� �Ǿ��ֱ� ������ �۵����� �ʴ´�. �ٸ� ��ü���� ���� �� ������ �߻��Ѵ�. �׷��� ������ template�� ������ �Ѵ�.
template <class T>
class RecordTable {
	int tableMaxSize;
	int topRecordTable;
	// RecordSet** data;
	//------------------------------------ ������ �ڵ� ------------------------------------//
	RecordSet<T>** data;
	//------------------------------------ ������ �ڵ� ------------------------------------//
	int capacity;
public:
	RecordTable(int numberSet, int numberRecords) :tableMaxSize(numberSet), capacity(numberRecords) {
		topRecordTable = 0;
		data = new RecordSet<T> *[numberSet];//10���� set
		for (int i = 0; i < numberSet; i++) {
			data[i] = new RecordSet<T>(numberRecords);//�� set�� 5�� records
		}
	}

	int Add(T*); // ���� �ϳ��� bag�� ����
	int Delete(char*);
	T* Search(char*);
	void Print();
};

template <class T>
int RecordTable<T>::Add(T* p) {
	int result = data[topRecordTable]->Add(p); // RecordSet�� Add() �޼ҵ� ȣ�� ��� ����
	if (result == 1) { // ���� �������� ���
		topRecordTable++; // topRecordTable ������ ������Ŵ
		if (topRecordTable == tableMaxSize) {
			cout << "���̺��� ���� á���ϴ�." << endl;
			// return 1; // ���̺��� ���� á���� �˸��� ���� 1�� ��ȯ
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
}//bag���� ���� �ϳ��� ����

template <class T>
T* RecordTable<T>::Search(char* str) {
	for (int i = 0; i < tableMaxSize; i++) {
		T* result = data[i]->Search(str);
		if (result != nullptr) {
			return result; // ���ڵ带 ���������� ã�� ���
		}
	}

	throw EmptySearchException();
	// return nullptr; // ã�� ���ڵ尡 ���� ���
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
		cout << "\n���� 1: member  ��ü 30�� �Է�, 2.table ���, 3: table ��ü ã��,4. table���� ��ü ����, 5. ����" << endl;
		cin >> select;
		switch (select) {
		case 1://table�� ��ü 30�� �Է�
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
			// table�� ��� ��ü ����ϱ�
			try {
				etable.Print();
				wtable.Print();
			}
			catch (Exception& error) {
				error.Print();
			}

			break;
		case 3:
			// table���� ��ü ã��
			try {
				e = etable.Search("kim");
				if (e == nullptr)
					cout << "kim�� �������� �ʴ´�" << endl;
				else
					e->Print();
				cout << endl;

				ws = wtable.Search("kim");
				if (ws == nullptr)
					cout << "kim�� �������� �ʴ´�" << endl;
				else
					ws->Print();
			}
			catch (Exception& error) {
				error.Print();
			}

			break;
		case 4:
			// table���� ��ü �����ϱ�
			try {
				result = etable.Delete("hong");
				if (result > 0)
					cout << "������ records ����" << result << endl;

				result = wtable.Delete("hong");
				if (result > 0)
					cout << "������ records ����" << result << endl;
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

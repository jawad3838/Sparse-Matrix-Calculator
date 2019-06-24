#include <iostream>
using namespace std;

class Node
{
public:
	int row;
	int column;
	float value;
	Node* next;
};

class Matrix
{
private:
	float det;
	Node *head, *conductor, *temp;
public:
	Matrix()
	{
		head = NULL;
		det = 1;
	}
	Node* Head()
	{
		return head;
	}
	void Insertion(int r, int c)
	{
		int rowNumber, columnNumber;
		float value;
		for (int i = 0; i < r*c; i++)
		{
		tag:
			cout << "Row Index: ";
			cin >> rowNumber;
			cout << "Column Index: ";
			cin >> columnNumber;
			cout << "Value: ";
			cin >> value;
			cout << endl;
			if (rowNumber == -1 && columnNumber == -1 && value == -1)
			{
				goto tag1;
			}
			else if (rowNumber < 0 || columnNumber < 0 || rowNumber >= r || columnNumber >= c)
			{
				cout << "Error: The Index is Out of Range\n\n";
				cout << endl;
				goto tag;
			}
			else if (value == 0)
			{
				cout << "Error: You can only enter non-zero values\n\n\n";
				goto tag;
			}
			else
			{
				int response = Insert(rowNumber, columnNumber, value);
				if (response == 1)
				{
					goto tag;
				}
			}
		}
	tag1:
		;
	}
	int Insert(int r, int c, float v)
	{
		conductor = head;
		while (conductor != NULL)
		{
			if (conductor->row == r && conductor->column == c)
			{
				cout << "Error: Value for the given index has already been added" << endl << endl;
				cout << endl;
				return 1;
			}
			conductor = conductor->next;
		}
		temp = new Node;
		temp->row = r;
		temp->column = c;
		temp->value = v;
		if (head == NULL)
		{
			head = temp;
			head->next = NULL;
		}
		else
		{
			conductor = head;
			Node* prev = NULL;
			while (conductor != NULL && (temp->row > conductor->row))
			{
				prev = conductor;
				conductor = conductor->next;
			}
			while (conductor != NULL && (temp->row == conductor->row) && (temp->column > conductor->column))
			{
				prev = conductor;
				conductor = conductor->next;
			}
			if (conductor == NULL)
			{
				temp->next = NULL;
				prev->next = temp;
			}
			else if (conductor == head)
			{
				temp->next = head;
				head = temp;
			}
			else
			{
				temp->next = conductor;
				prev->next = temp;
			}
		}
		return 0;
	}
	void Display(int rows, int columns)
	{
		cout << "Result: " << endl << endl;
		conductor = head;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (conductor == NULL)
				{
					cout << "0\t";
				}
				else if ((conductor->row == i) && (conductor->column == j))
				{
					cout << conductor->value << "\t";
					conductor = conductor->next;
				}
				else
				{
					cout << "0\t";
				}
			}
			cout << endl;
		}
	}
	void Add(Node* pointer1, int r, int c)
	{
		Node* pointer2 = head;
		if (pointer1 == NULL)
		{
			goto A1;
		}
		else if (pointer2 == NULL)
		{
			head = pointer1;
			goto A1;
		}
		else
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (pointer1 == NULL)
					{
						goto A1;
					}
					else if (pointer2 == NULL)
					{
						while (pointer1 != NULL)
						{
							Insert(pointer1->row, pointer1->column, pointer1->value);
							pointer1 = pointer1->next;
						}
						goto A1;
					}
					else if ((pointer2->row == i) && (pointer2->column == j) && (pointer1->row == i) && (pointer1->column == j))
					{
						pointer2->value += pointer1->value;
						pointer1 = pointer1->next;
						pointer2 = pointer2->next;
					}
					else if ((pointer1->row == i) && (pointer1->column == j))
					{
						Insert(pointer1->row, pointer1->column, pointer1->value);
						pointer1 = pointer1->next;
					}
					else if ((pointer2->row == i) && (pointer2->column == j))
					{
						pointer2 = pointer2->next;
					}
					else
					{
					}
				}
			}
		}
	A1:
		Display(r, c);
	}
	void Inverse(Node* p)
	{
		conductor = p;
		while (p != NULL)
		{
			p->value *= -1;
			p = p->next;
		}
	}
	void Subtract(Node* pointer2, int r, int c)
	{
		Node* pointer1 = head;
		if (pointer2 == NULL)
		{
			goto A1;
		}
		else if (pointer1 == NULL)
		{
			Inverse(pointer2);
			head = pointer2;
			goto A1;
		}
		else
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (pointer2 == NULL)
					{
						goto A1;
					}
					else if (pointer1 == NULL)
					{
						while (pointer2 != NULL)
						{
							Insert(pointer2->row, pointer2->column, (pointer2->value * -(1)));
							pointer2 = pointer2->next;
						}
						goto A1;
					}
					else if ((pointer1->row == i) && (pointer1->column == j) && (pointer2->row == i) && (pointer2->column == j))
					{
						pointer1->value -= pointer2->value;
						pointer2 = pointer2->next;
						pointer1 = pointer1->next;
					}
					else if ((pointer2->row == i) && (pointer2->column == j))
					{
						Insert(pointer2->row, pointer2->column, (pointer2->value * (-1)));
						pointer2 = pointer2->next;
					}
					else if ((pointer1->row == i) && (pointer1->column == j))
					{
						pointer1 = pointer1->next;
					}
					else
					{
					}
				}
			}
		}
	A1:
		Display(r, c);
	}
	void ScalarMul(Node* p, int r, int c, float s)
	{
		while (p != NULL)
		{
			p->value *= s;
			p = p->next;
		}
		Display(r, c);
	}
	void Mul(Node* p1, Node* p2, int r1, int c1, int r2, int c2)
	{
		if (p1 == NULL || p2 == NULL)
		{
			goto mul1;
		}
		else
		{
			Node* h1 = p1;
			Node* h2 = p2;
			float product = 0;
			for (int i = 0; i < r1; i++)
			{
				for (int j = 0; j < r2; j++)
				{
					p1 = h1;
					p2 = h2;
					product = 0;
					while (p1 != NULL && p1->row < i)
					{
						p1 = p1->next;
					}
					if (p1 == NULL)
					{
						goto mul1;
					}
					while (p2 != NULL && p2->row < j)
					{
						p2 = p2->next;
					}
					if (p2 == NULL)
					{
						goto mul3;
					}
					for (int k = 0; k < c1; k++)
					{
						if (p1 == NULL || p2 == NULL)
						{
							goto mul2;
						}
						else if (p1->row == i && p2->row == j)
						{
							if (p1->column == p2->column)
							{
								product += p1->value * p2->value;
								p1 = p1->next;
								p2 = p2->next;
							}
							else if (p1->column < p2->column)
							{
								p1 = p1->next;
							}
							else
							{
								p2 = p2->next;
							}
						}
						else
						{
							goto mul2;
						}
					}
				mul2:
					if (product != 0)
					{
						Insert(i, j, product);
					}
				}
			mul3:
				;
			}
		}
	mul1:
		;
	}
	void Transpose(Node* p)
	{
		while (p != NULL)
		{
			Insert(p->column, p->row, p->value);
			p = p->next;
		}
	}
	int ZeroRow(int r)
	{
		conductor = head;
		for (int i = 0; i < r; i++)
		{
			while (conductor != NULL && conductor->row < i)
			{
				conductor = conductor->next;
			}
			if (conductor == NULL || conductor->row != i)
			{
				return 1;
			}
		}
		return 0;
	}
	int EchelonCheck(int r)
	{
		Node* p = head;
		for (int i = 0; i < (r - 1); i++)
		{
			while (p != NULL && p->row < i)
			{
				p = p->next;
			}
			if (p == NULL)
			{
				return 0;
			}
			int prev = p->column;
			while (p != NULL && p->row < (i + 1))
			{
				p = p->next;
			}
			if (p == NULL)
			{
				return 0;
			}
			int current = p->column;
			if (current <= prev)
			{
				return 1;
			}
		}
	}
	int ZeroRows(int r)
	{
		int tail;
		Node *previous, *last, *del, *point;
		previous = last = temp = NULL;
		point = head;
		for (int i = 0; i < r; i++)
		{
			point = head;
			while (point != NULL && point->row < i)
			{
				previous = point;
				point = point->next;
			}
			if (point == NULL)
			{
				return 0;
			}
			if (point->row != i)
			{
				last = head;
				while (last->next != NULL)
				{
					last = last->next;
				}
				tail = last->row;
				last = head;
				while (last->row < tail)
				{
					last = last->next;
				}
				while (1)
				{
					Insert(i, last->column, last->value);
					point = head;
					while (point->row < last->row)
					{
						previous = point;
						point = point->next;
					}
					del = last;
					last = last->next;
					if (last == NULL)
					{
						previous->next = NULL;
						delete del;
						det *= -1;
						return 1;
					}
					else
					{
						previous->next = last;
						delete del;
					}
				}
			}
		}
	}
	int Pivot(int r, int c)
	{
		Node *previous, *last, *del, *point, *point2;
		previous = last = NULL;
		point = head;
		while (1)
		{
			point = head;
			for (int i = 0; i < (r - 1); i++)
			{
				while (point != NULL && point->row < i)
				{
					last = point;
					point = point->next;
				}
				if (point == NULL)
				{
					return 0;
				}
				int pivot1 = point->column;
				point2 = head;
				while (point2 != NULL && point2->row < (i + 1))
				{
					previous = point2;
					point2 = point2->next;
				}
				if (point2 == NULL)
				{
					return 0;
				}
				int pivot2 = point2->column;
				if (pivot2 < pivot1)
				{
					for (int j = 0; j < c; j++)
					{
						if (point->column == j && point2->column == j)
						{
							float swap = point->value;
							point->value = point2->value;
							point2->value = swap;
							if (point->next != NULL)
							{
								last = point;
								point = point->next;
							}
							if (point2->next != NULL)
							{
								previous = point2;
								point2 = point2->next;
							}
						}
						else if (point2->column == j)
						{
							float swap = point2->value;
							del = point2;
							if (del->next == NULL)
							{
								previous->next = NULL;
								previous = NULL;
								delete del;
								Insert(i, j, swap);
								last = temp;
								point2 = temp;
							}
							else
							{
								previous->next = point2->next;
								delete del;
								Insert(i, j, swap);
								last = temp;
								point2 = previous->next;
							}
						}
						else if (point->column == j)
						{
							float swap = point->value;
							del = point;
							if (del->next == NULL)
							{
								last->next = NULL;
								delete del;
								Insert(i + 1, j, swap);
								previous = temp;
								point = temp;
							}
							else
							{
								last->next = point->next;
								delete del;
								Insert(i + 1, j, swap);
								previous = temp;
								point = last->next;
							}
						}
						else
						{
							;
						}
					}
					det *= -1;
					return 1;
				}
			}
			return 0;
		}
	}
	int RowOperation(int r, int c)
	{
		Node *point, *point2, *prev, *prev2, *del, *temporary;
		prev = prev2 = NULL;
		point = head;
		for (int i = 0; i < (r - 1); i++)
		{
			while (point != NULL && point->row < i)
			{
				prev = point;
				point = point->next;
			}
			if (point == NULL)
			{
				return 0;
			}
			int pivot = point->column;
			point2 = head;
			while (point2 != NULL && point2->row < (i + 1))
			{
				prev2 = point2;
				point2 = point2->next;
			}
			if (point2 == NULL)
			{
				return 0;
			}
			int pivot2 = point2->column;
			if (pivot == pivot2)
			{
				float pivotValue = point->value;
				float pivotValue2 = point2->value;
				det *= pivotValue;
				for (int j = 0; j < c; j++)
				{
					if (point->column == j && point2->column == j)
					{
						point2->value = (point2->value * pivotValue) - (point->value * pivotValue2);
						if (point->next != NULL)
						{
							point = point->next;
						}
						if (point2->next != NULL)
						{
							point2 = point2->next;
						}
					}
					else if (point->column == j)
					{
						Insert(i + 1, j, -(point->value * pivotValue2));
						if (point->next != NULL)
						{
							point = point->next;
						}
					}
					else if (point2->column == j)
					{
						if (point2->next != NULL)
						{
							point2 = point2->next;
						}
					}
				}
				del = prev2;
				while (prev2->next != NULL && del->row < (i + 2))
				{
					if (del->value == 0)
					{
						temporary = del;
						del = del->next;
						prev2->next = del;
						delete temporary;
					}
					else
					{
						prev2 = del;
						del = del->next;
					}
					if (del == NULL)
					{
						return 1;
					}
				}
				return 1;
			}
		}
		return 0;
	}
	void PivotOne(int r)
	{
		conductor = head;
		for (int i = 0; i < r; i++)
		{
			float pivotValue = conductor->value;
			while (conductor->row == i)
			{
				conductor->value = conductor->value / pivotValue;
				conductor = conductor->next;
				if (conductor == NULL)
				{
					goto p1;
				}
			}
		}
	p1:
		;
	}
	void ReducedRowOperation(int r)
	{
		int pivotID = 1;
		float prevStart, prevPivot;
		Node* start = head;
		Node* pivot = head;
		Node* p = head;
		for (int i = 0; i < r; i++)
		{
			while (p->row < i)
			{
				p = p->next;
			}
			if (p == NULL)
			{
				goto rro;
			}
			start = p;
			while (p->row < (i + 1))
			{
				pivot = p;
				p = p->next;
				if (p == NULL)
				{
					goto rro1;
				}
			}
		rro1:
			if (pivot != start)
			{
				if (pivot->column == pivotID)
				{
					pivotID++;
				pt:
					prevStart = start->value;
					prevPivot = pivot->value;
					start->value -= (prevStart / prevPivot) * prevPivot;
					start = start->next;
					if (pivot != start)
					{
						goto pt;
					}
				}
				else
				{
					start->value -= (prevStart / prevPivot) * pivot->value;
				}
			}
		}
	rro:
		;
	}
	void ZeroIllimination()
	{
		Node *previous, *del;
		previous = del = NULL;
		conductor = head;
		while (conductor != NULL)
		{
			if (conductor->value == 0)
			{
				del = conductor;
				conductor = conductor->next;
				previous->next = conductor;
				delete del;
			}
			else
			{
				previous = conductor;
				conductor = conductor->next;
			}
		}
	}
	void Echelon(int r, int c, int reduced)
	{
		int check = EchelonCheck(r);
		if (check == 0)
		{
			goto re4;
		}
		else
		{
		re2:
			int zero = ZeroRows(r);
			while (zero == 1)
			{
				check = EchelonCheck(r);
				if (check == 0)
				{
					goto re4;
				}
				else
				{
					zero = ZeroRows(r);
				}
			}
			int pivot = Pivot(r, c);
			while (pivot == 1)
			{
				check = EchelonCheck(r);
				if (check == 0)
				{
					goto re4;
				}
				else
				{
					pivot = Pivot(r, c);
				}
			}
			int rowOperation = RowOperation(r, c);
			if (rowOperation == 0)
			{
				goto re4;
			}
			else
			{
				check = EchelonCheck(r);
				if (check == 0)
				{
					goto re4;
				}
				else
				{
					goto re2;
				}
			}
		}
	re4:
		if (reduced == 1)
		{
			goto re5;
		}
		else if (reduced == 2)
		{
			int rank;
			conductor = head;
			while (conductor->next != NULL)
			{
				conductor = conductor->next;
			}
			system("cls");
			cout << "Rank: " << conductor->row + 1 << endl;
			goto re5;
		}
		else if (reduced == 3)
		{
			float determinant = 1;
			conductor = head;
			temp = head;
			while (conductor != NULL)
			{
				determinant *= conductor->value;
			deter:
				temp = conductor->next;
				if (temp == NULL)
				{
					determinant /= det;
					system("cls");
					cout << "Determinant: " << determinant << endl << endl << endl;
					system("pause");
					goto re5;
				}
				while (temp->row == conductor->row)
				{
					conductor = temp;
					temp = temp->next;
					if (temp == NULL)
					{
						if (conductor->row != r)
						{
							cout << "The Determinant is equal to zero" << endl << endl << endl;
							system("pause");
							goto re5;
						}
						determinant /= det;
						system("cls");
						cout << "Determinant: " << determinant << endl << endl << endl;
						system("pause");
						goto re5;
					}
				}
				determinant *= temp->value;
				conductor = temp;
				goto deter;
			}
		}
		PivotOne(r);
		Display(r, c);
	re5:
		;
	}
	void DeleteList()
	{
		temp = head;
		conductor = head;
		while (conductor != 0)
		{
			temp = conductor;
			conductor = conductor->next;
			delete temp;
		}
		head = 0;
	}
	void SubtractRow(Node *node, float val, int row, int columns, float pivot, int rows) //Row = current row, Rows = Total rows
	{
		Node *temp = head;
		static int i = 1;
		Node *zeroCheck = node;
		Node *prev = zeroCheck;
		for (int j = (node->column) + 1; j < columns; j++)
		{
			if ((node->next))
			{
				if ((node->next)->row == row && (node->next)->column == j)
				{
					node = node->next;
					while (temp != NULL)
					{
						if (temp->row == row - i && temp->column == j)
						{
							node->value = node->value - ((val / pivot) * temp->value);
							break;
						}
						temp = temp->next;
					}
				}
			}
			else break;
		}
		temp = head;
		temp = temp->next;
		zeroCheck = zeroCheck->next;
		Node *temp1 = zeroCheck;
		while (temp != NULL && temp->row == row - i)
		{
			int found = 0;
			zeroCheck = temp1;
			while (zeroCheck->row == row && zeroCheck->column != temp->column)
			{
				prev = zeroCheck;
				zeroCheck = zeroCheck->next;
				if (zeroCheck == NULL) break;
			}
			if (zeroCheck)
			{

				if ((zeroCheck->column == temp->column) && zeroCheck->row == row) found = 1;
				else found = 0;

				if (found == 0)
				{
					Node *newNode = new Node();
					newNode->row = row;
					newNode->column = temp->column;
					newNode->value = -(val / pivot) * temp->value;
					prev->next = newNode;
					newNode->next = zeroCheck;
					prev = newNode;
				}
			}
			temp = temp->next;
		}
		i++;
		if (row == rows - 1)
			i = 1;        //Performing row operation on last row
	}
	void LUFactorization(int r, int c)
	{
		Matrix M;
		float pivot = 0;
		float subtract = 0;
		for (int i = 0; i < r; i++)                //Create Identity Matrix Of Size r
		{
			M.Insert(i, i, 1);
		}
		conductor = head;
		for (int j = 0; j < (c - 1); j++)                       //Last diagonal element needs no check
		{
		tag:
			if (conductor)
			{
				if (conductor->row == conductor->column && conductor->row == j)      //select diagonal element as pivot
				{
					pivot = conductor->value;
					Node *temp = conductor;
					conductor = conductor->next;
					for (int i = (temp->row) + 1; i < r; i++)           //perform row operation on next row
					{
					intag:
						if (temp)
						{
							if (temp->column == j && temp->row == i)        //get the entry directly below the pivot
							{
								subtract = temp->value;
								M.Insert(i, j, subtract / pivot);
								SubtractRow(temp, subtract, i, c, pivot, r);   //subtract row
								temp->value = 0;
								temp = temp->next;
							}
							else
							{
								temp = temp->next;
								goto intag;
							}
						}
					}
					goto tag1;
				}
				else
				{
					conductor = conductor->next;
					goto tag;
				}
			}

		tag1:
			;
		}
		cout << "Upper Triangle ";
		Display(r, c);              //Display Upper Triangular Matrix
		cout << "\n\n\nLower Triangle ";
		M.Display(r, c);		   //Display Lower Triangular Matrix
	}
	int Menu()
	{
		while (1)
		{
			system("cls");
			int choice;
			cout << "Select a Sparse Matrix Operation:\n\n1)Addition\n\n2)Subtraction\n\n3)Scalar Multiplication\n\n4)Multiplication\n\n5)Transpose\n\n6)Determinant\n\n7)Row Echelon Form\n\n8)Reduced Row Echelon\n\n9)Rank\n\n10)LU-Factorization\n\n11)Exit\n\n\nEnter your Choice: ";
			cin >> choice;
			switch (choice)
			{
			case(1) :
			{
						system("cls");
						int rows, columns;
					a:
						cout << "Enter the Size of the Matrices\n\nRows: ";
						cin >> rows;
						cout << "Columns: ";
						cin >> columns;
						cout << endl;
						if (rows < 1 || columns < 1)
						{
							cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							goto a;
						}
						system("pause");
						Matrix M1, M2;
						system("cls");
						cout << "Enter the Values of the First Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M1.Insertion(rows, columns);
						system("cls");
						cout << "Enter the Values of the Second Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M2.Insertion(rows, columns);
						system("cls");
						M2.Add(M1.Head(), rows, columns);
						cout << endl << endl;
						system("pause");
						break;
			}
			case(2) :
			{
						system("cls");
						int rows, columns;
					b:
						cout << "Enter the Size of the Matrices\n\nRows: ";
						cin >> rows;
						cout << "Columns: ";
						cin >> columns;
						cout << endl;
						if (rows < 1 || columns < 1)
						{
							cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							goto b;
						}
						system("pause");
						Matrix M1, M2;
						system("cls");
						cout << "Enter the Values of the First Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M1.Insertion(rows, columns);
						system("cls");
						cout << "Enter the Values of the Second Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M2.Insertion(rows, columns);
						system("cls");
						M1.Subtract(M2.Head(), rows, columns);
						cout << endl << endl;
						system("pause");
						break;
			}
			case(3) :
			{
						system("cls");
						int rows, columns;
						float multiple;
					c:
						cout << "Enter the Size of the Matrix\n\nRows: ";
						cin >> rows;
						cout << "Columns: ";
						cin >> columns;
						cout << endl;
						if (rows < 1 || columns < 1)
						{
							cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							goto c;
						}
						system("pause");
						system("cls");
						Matrix M1;
						cout << "Enter the Values of the Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M1.Insertion(rows, columns);
						system("cls");
						cout << "Enter the Scalar Multiple: ";
						cin >> multiple;
						system("cls");
						M1.ScalarMul(M1.Head(), rows, columns, multiple);
						cout << endl << endl;
						system("pause");
						break;
			}
			case(4) :
			{
						system("cls");
						int rows1, rows2, columns1, columns2;
						Matrix M1, M2, M3, M4;
					d1:
						cout << "Enter the Size of the First Matrix\n\nRows: ";
						cin >> rows1;
						cout << "Columns: ";
						cin >> columns1;
						cout << endl;
						if (rows1 < 1 || columns1 < 1)
						{
							cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							goto d1;
						}
						system("pause");
						system("cls");
						cout << "Enter the Values of the First Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M1.Insertion(rows1, columns1);
						system("pause");
						system("cls");
					m1:
						cout << "Enter the Size of the Second Matrix\n\nRows: ";
						cin >> rows2;
						cout << "Columns: ";
						cin >> columns2;
						cout << endl;
						if (columns1 != rows2)
						{
							cout << "Error: Number of Columns of the First Matrix are not equal to Number of Rows of the Second Matrix" << endl << endl;
							goto m1;
						}
						if (rows2 < 1 || columns2 < 1)
						{
							cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							goto m1;
						}
						system("pause");
						system("cls");
						cout << "Enter the Values of the Second Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M2.Insertion(rows2, columns2);
						M3.Transpose(M2.Head());
						M4.Mul(M1.Head(), M3.Head(), rows1, columns1, columns2, rows2);
						M4.Display(rows1, columns2);
						cout << endl << endl;
						system("pause");
						break;
			}
			case(5) :
			{
						system("cls");
						int rows, columns;
					e:
						cout << "Enter the Size of the Matrix\n\nRows: ";
						cin >> rows;
						cout << "Columns: ";
						cin >> columns;
						cout << endl;
						if (rows < 1 || columns < 1)
						{
							cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							goto e;
						}
						system("pause");
						system("cls");
						Matrix M1, M2;
						cout << "Enter the Values of the Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M1.Insertion(rows, columns);
						system("cls");
						M2.Transpose(M1.Head());
						M2.Display(columns, rows);
						cout << endl << endl;
						system("pause");
						break;
			}
			case(6) :
			{
						system("cls");
						int rows, columns;
					f:
						cout << "Enter the Size of the Matrix\n\nRows: ";
						cin >> rows;
						cout << "Columns: ";
						cin >> columns;
						cout << endl;
						if (rows < 1 || columns < 1)
						{
							cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							goto f;
						}
						if (rows != columns)
						{
							cout << "Error: You can only enter a square matrix i.e. : Number of rows and columns are equal" << endl << endl;
							goto f;
						}
						Matrix M1, M2;
						system("pause");
						system("cls");
						cout << "Enter the Values of the Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M1.Insertion(rows, columns);
						M2.Transpose(M1.Head());
						system("cls");
						if (M1.ZeroRow(rows) || M2.ZeroRow(rows))
						{
							cout << "The Determinant is equal to zero" << endl << endl;
							system("pause");
							goto f1;
						}
						else
						{
							M2.DeleteList();
							M1.Echelon(rows, columns, 3);
						}
					f1:
						;
						break;
			}
			case(7) :
			{
						system("cls");
						int rows, columns;
					g:
						cout << "Enter the Size of the Matrix\n\nRows: ";
						cin >> rows;
						cout << "Columns: ";
						cin >> columns;
						cout << endl;
						if (rows < 1 || columns < 1)
						{
							cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							goto g;
						}
						system("pause");
						system("cls");
						Matrix M1;
						cout << "Enter the Values of the Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M1.Insertion(rows, columns);
						system("cls");
						M1.Echelon(rows, columns, 0);
						cout << endl << endl;
						system("pause");
						break;
			}
			case(8) :
			{
						system("cls");
						int rows, columns;
					h:
						cout << "Enter the Size of the Matrix\n\nRows: ";
						cin >> rows;
						cout << "Columns: ";
						cin >> columns;
						cout << endl;
						if (rows < 1 || columns < 1)
						{
							cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							goto h;
						}
						system("pause");
						system("cls");
						Matrix M1;
						cout << "Enter the Values of the Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M1.Insertion(rows, columns);
						system("cls");
						M1.Echelon(rows, columns, 1);
						Matrix M2, M3;
						M2.Transpose(M1.Head());
						M1.DeleteList();
						M2.ReducedRowOperation(columns);
						M2.ZeroIllimination();
						M3.Transpose(M2.Head());
						M2.DeleteList();
						M3.PivotOne(rows);
						M3.Display(rows, columns);
						cout << endl << endl;
						system("pause");
						break;
			}
			case(9) :
			{
						system("cls");
						int rows, columns;
					i:
						cout << "Enter the Size of the Matrix\n\nRows: ";
						cin >> rows;
						cout << "Columns: ";
						cin >> columns;
						cout << endl;
						if (rows < 1 || columns < 1)
						{
							cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							goto i;
						}
						system("pause");
						system("cls");
						Matrix M1;
						cout << "Enter the Values of the Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						M1.Insertion(rows, columns);
						system("cls");
						M1.Echelon(rows, columns, 2);
						cout << endl << endl;
						system("pause");
						break;
			}
			case(10) :
			{
						 system("cls");
						 int rows, columns;
					 j:
						 cout << "Enter the Size of the Matrix\n\nRows: ";
						 cin >> rows;
						 cout << "Columns: ";
						 cin >> columns;
						 cout << endl;
						 if (rows < 1 || columns < 1)
						 {
							 cout << "Error: The minimum value for the rows and columns is 1" << endl << endl;
							 goto j;
						 }
						 system("pause");
						 system("cls");
						 Matrix M1;
						 cout << "Enter the Values of the Matrix (Enter -1 in each entry to stop)\n" << endl << endl;
						 M1.Insertion(rows, columns);
						 system("cls");
						 M1.LUFactorization(rows, columns);
						 cout << endl << endl;
						 system("pause");
						 break;
			}
			case(11) :
			{
						 cout << endl << endl;
						 goto exit;
						 break;
			}
			default:
			{
					   cout << endl << endl << "Error: Incorrect Option" << endl << endl;
					   system("pause");
					   break;
			}
			}
		}
		system("pause");
	exit:
		return 0;
	}
};

int main()
{
	Matrix M;
	
	M.Menu();

	system("pause");
	return 0;
}
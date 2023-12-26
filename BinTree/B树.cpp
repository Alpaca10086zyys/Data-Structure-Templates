#include <iostream>
#include <vector>

using namespace std;

#define degree 512
#define Maxsize 511
#define Minsize 256
#define mid 256

#include <ctime> 
#include<stdlib.h>
#include <algorithm>
#define size 10000

struct BNode
{
	int* key = new int[degree]();//��һ������ʱ���ã����������ȡ������
	BNode** children = new BNode * [degree+1]();
	BNode* father = nullptr;

	int keysize = 0;
//	int childsize = 0;
	bool ifleaf = true;

};

struct position
{
	BNode* node = nullptr;
	int i = 0;
};

BNode* insert(int val, BNode* root)
{
	BNode* temp = root;
	//ʹ������Ҷ�ӽڵ��Ͻ���
	while (temp->ifleaf != true)
	{
		int i = 0;
		while (i < temp->keysize && temp->key[i] < val)
		{
			i++;
		}
		temp = temp->children[i];
	}
	
	//����
	int i = temp->keysize;
	while (i != 0 && temp->key[i - 1] > val)
	{
		temp->key[i] = temp->key[i - 1];
		i--;
	}
	if (i != 0 &&temp->key[i - 1] == val)
	{
		i++;
		while (i < temp->keysize)
		{
			temp[i] = temp[i + 1];
			i++;
		}
		temp->key[temp->keysize] = 0;
		return root;
	}
	temp->key[i] = val;
	temp->keysize++;
	
	//����Ƿ���
	while (temp != root)
	{
		if (temp->keysize > Maxsize)
		{
			BNode* pa = temp->father;
			int insert = temp->key[mid];
			int i = pa->keysize;
			while (i != 0 && pa->key[i - 1] > insert)
			{
				pa->key[i] = pa->key[i - 1];
				pa->children[i+1] = pa->children[i];
				i--;
			}
			pa->key[i] = insert;
			BNode* newleft = new BNode;
			newleft->father = pa;
			BNode* newright = new BNode;
			newright->father = pa;
			for (int j = 0; j < mid; j++)
			{
				newleft->key[j] = temp->key[j];
				newleft->children[j] = temp->children[j];
				if (temp->children[j] != nullptr)
				{
					temp->children[j]->father = newleft;
				}
			}
			newleft->children[mid] = temp->children[mid];
			if (temp->children[mid] != nullptr)
			{
				temp->children[mid]->father = newleft;
			}
			newleft->keysize = mid;
			for (int j = mid + 1; j < temp->keysize; j++)
			{
				newright->key[j - mid - 1] = temp->key[j];
				newright->children[j - mid - 1] = temp->children[j];
				if (temp->children[j] != nullptr)
				{
					temp->children[j]->father = newright;
				}
			}
			newright->children[temp->keysize - mid - 1] = temp->children[degree];
			if (temp->children[degree] != nullptr)
			{
				temp->children[degree]->father = newright;
			}
			newright->keysize = temp->keysize - mid-1;

			pa->children[i] = newleft;
			pa->children[i + 1] = newright;
			pa->keysize++;
			if (newleft->children[0] != nullptr)
			{
				newleft->ifleaf = false;
			}
			if (newright->children[0] != nullptr)
			{
				newright->ifleaf = false;
			}

			delete temp;
			temp = pa;

		}
		else
		{
			break;
		}
	}

	if (temp == root)
	{
		if (temp->keysize > Maxsize)
		{
			BNode* pa = new BNode;
			pa->ifleaf = false;
			int insert = temp->key[mid];
			BNode* newleft = new BNode;
			newleft->father = pa;
			BNode* newright = new BNode;
			newright->father = pa;
			for (int j = 0; j < mid; j++)
			{
				newleft->key[j] = temp->key[j];
				newleft->children[j] = temp->children[j];
				if (temp->children[j] != nullptr)
				{
					temp->children[j]->father = newleft;
				}
			}
			newleft->children[mid] = temp->children[mid];
			if (temp->children[mid] != nullptr)
			{
				temp->children[mid]->father = newleft;
			}
			newleft->keysize = mid;
			for (int j = mid + 1; j < temp->keysize; j++)
			{
				newright->key[j - mid - 1] = temp->key[j];
				newright->children[j - mid - 1] = temp->children[j];
				if (temp->children[j] != nullptr)
				{
					temp->children[j]->father = newright;
				}
			}
			newright->children[temp->keysize - mid - 1] = temp->children[degree];
			if (temp->children[degree] != nullptr)
			{
				temp->children[degree]->father = newright;
			}
			newright->keysize = temp->keysize - mid - 1;

			pa->key[0] = insert;
			pa->children[0] = newleft;
			pa->children[1] = newright;
			pa->keysize = 1;
			if (newleft->children[0] != nullptr)
			{
				newleft->ifleaf = false;
			}
			if (newright->children[0] != nullptr)
			{
				newright->ifleaf = false;
			}
			delete temp;
			temp = pa;
			root = pa;
			
		}
	}

	return root;
}

position *search(int val, BNode* root)
{
	BNode* temp = root;
	int i = 0;
	position* ans = new position();

	if (temp == nullptr)
	{
		return ans ;
	}

	while ( temp != nullptr && temp->key[i] != val)
	{
		if (temp->key[i] < val && i < temp->keysize)
		{
			i++;
		}
		else if (i == temp->keysize)
		{
			temp = temp->children[i];
			i = 0;
		}
		else if (temp->key[i] > val)
		{
			temp = temp->children[i];
			i = 0;
		}
	}

	if (temp == nullptr)
	{
		ans->node = nullptr;
		return ans;
	}

	ans->node = temp;
	ans->i = i;

	return ans;
}

BNode* earse(int val, BNode* root)
{
	position* p = search(val, root);
	if (p->node == nullptr)
	{
		return nullptr;
	}
	
	BNode* temp = p->node;
	if (temp->ifleaf == true)
	{
		int i = p->i;
		while (i+1 <= temp->keysize)
		{
			temp->key[i] = temp->key[i + 1];
			i++;
		}
		temp->keysize--;
	}
	else
	{
		temp = temp->children[p->i + 1];
		while (temp->ifleaf != true)
		{
			temp = temp->children[0];
		}
		p->node->key[p->i] = temp->key[0];
		int i = 0;
		while (i + 1 <= temp->keysize)
		{
			temp->key[i] = temp->key[i + 1];
			i++;
		}
		temp->keysize--;

	}

	while (temp!= root)
	{
		if (temp->keysize < Minsize)
		{
			BNode* pa = temp->father;
			int j = 0;
			while (pa->children[j] != temp)
			{
				j++;
			}

			BNode *brother = nullptr;
			if ((j!= pa->keysize )&&((j==0) || pa->children[j + 1]->keysize >= pa->children[j - 1]->keysize))
			{
				brother = pa->children[j + 1];
			}
			else if (j == pa->keysize|| pa->children[j + 1]->keysize < pa->children[j-1]->keysize)
			{
				brother = pa->children[j-1];
			}

			if (brother->keysize > Minsize)
			{
				if (brother->key[0] < temp->key[0])
				{
					temp->children[temp->keysize + 1] = temp->children[temp->keysize];
					for (int i = temp->keysize-1; i>=0; i--)
					{
						temp->key[i + 1] = temp->key[i];
						temp->children[i + 1] = temp->children[i];
					}
					temp->children[0] = brother->children[brother->keysize];
					if (temp->children[0] != nullptr)
					{
						temp->children[0]->father = temp;
					}
					brother->children[brother->keysize] = nullptr;
					temp->key[0] = pa->key[j - 1];
					pa->key[j - 1] = brother->key[brother->keysize - 1];
					brother->key[brother->keysize - 1] = 0;
					brother->keysize--;
					temp->keysize++;
				}
				else
				{
					
					temp->children[temp->keysize + 1] = brother->children[0];
					if (brother->children[0] != nullptr)
					{
						brother->children[0]->father = temp;
					}
					brother->children[0] = nullptr;
					temp->key[temp->keysize] = pa->key[j];
					pa->key[j] = brother->key[0];
					for (int k = 0; k < brother->keysize; k++)
					{
						brother->key[k] = brother->key[k + 1];
						brother->children[k] = brother->children[k + 1];
					}
					brother->children[brother->keysize] = brother->children[brother->keysize + 1];
					brother->keysize--;
					temp->keysize++;

				}

				return root;
			}
			else
			{
				if (brother->key[0] < temp->key[0])
				{
					brother->key[brother->keysize] = pa->key[j - 1];
					pa->keysize--;
					brother->children[brother->keysize + 1] = temp->children[0];
					if (temp->children[0] != nullptr)
					{
						brother->children[brother->keysize + 1]->father = brother;
					}
					brother->keysize++;
					for (int i = 0; i < temp->keysize; i++)
					{
						brother->key[brother->keysize + i] = temp->key[i];
						brother->children[brother->keysize + i + 1] = temp->children[i + 1];
						if (temp->children[i + 1] != nullptr)
						{
							temp->children[i + 1]->father = brother;
						}
						
					}
					brother->keysize += temp->keysize;
					
					pa->children[j] = nullptr;
					delete temp;

					for (int k = j - 1; k < pa->keysize + 1; k++)
					{
						pa->key[k] = pa->key[k + 1];
						pa->children[k + 1] = pa->children[k + 2];
					}
					
					if (pa->keysize == 0)
					{
						delete root;
						root = brother;
						brother->father = nullptr;
					}

					temp = brother;
				}
				else
				{		
					temp->key[temp->keysize] = pa->key[j];
					pa->keysize--;
					temp->children[temp->keysize + 1] = brother->children[0];
					if (brother->children[0] != nullptr)
					{
						temp->children[temp->keysize + 1]->father = temp;
					}
					temp->keysize++;
					for (int i = 0; i < brother->keysize; i++)
					{
						temp->key[temp->keysize + i] = brother->key[i];
						temp->children[temp->keysize + i + 1] = brother->children[i + 1];
						if (brother->children[i + 1] != nullptr)
						{
							brother->children[i + 1]->father = temp;
						}

					}
				    temp->keysize += brother->keysize;
					
					pa->children[j+1] = nullptr;
					delete brother;

					for (int k = j ; k < pa->keysize + 1; k++)
					{
						pa->key[k] = pa->key[k + 1];
						pa->children[k + 1] = pa->children[k + 2];
					}
				//	pa->children[pa->keysize + 2] = pa->children[pa->keysize + 3];

					if (root->keysize == 0)
					{
						delete root;
						root = temp;
						temp->father = nullptr;
					}
					
					temp = pa;
				}
			}
		}
		else
		{
			break;
		}

		
	}

	delete p;
	return root;
	
}
int main(void)
{
	/*BNode* root = new BNode;
	vector <int> input = {6,5,4,3,2,1};
	for (int i = 0; i < input.size(); i++)
	{
		root = insert(input[i], root);
	}*/

	//position* p = search(21,root);
	//root = earse(21, root);
	//root = earse(27, root);
	//root = earse(32, root);
	//root = earse(40, root);

	vector<int> input;
	input.resize(size);
	srand(unsigned(time(0)));
	const int MAX = size * 10;
	const int MIN = 1;
	for (int i = 0; i < size; i++)
	{
		int data = rand() % (MAX - MIN + 1) + MIN;//���ĺ���
		input[i] = data;
	}

	sort(input.begin(), input.end());
	//sort(input.rbegin(), input.rend());

	BNode* root = new BNode;
	clock_t first = clock();
	for (int i = 0; i < size; i++)
	{
		root = insert(input[i], root);
	}
	clock_t second = clock();
	cout << double(second - first) / CLOCKS_PER_SEC * 100 << "\n";
	for (int i = 0; i < 1000; i++)
	{
		int pos = rand() % size;
		search(input[pos], root);
	}
	clock_t third = clock();
	cout << double(third - second) / CLOCKS_PER_SEC * 100 << "\n";

    sort(input.begin(), input.end());
	//sort(input.rbegin(), input.rend());
	third = clock();
	for (int i = 0; i < size; i++)
	{
		root = earse(input[i], root);
	}

	clock_t forth = clock();
	cout << double(forth - third) / CLOCKS_PER_SEC * 100 << "\n";

	//root = earse(24, root);
	//return 0;
	

	
	return 0;
}





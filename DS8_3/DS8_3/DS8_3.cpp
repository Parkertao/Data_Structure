// DS8_3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stack>



 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

	ListNode* res = new ListNode;
	//ListNode res;
	int o = 0, n = 0;
	while (l1 != NULL || l2 != NULL)
	{
		n = (l1->val + l2->val) % 10;
		o = (l1->val + l2->val) / 10;
		res->val += n;
		res->next = new ListNode(o);
		l1 = l1->next;
		l2 = l2->next;
		res = res->next;
	}
	return res;
}
int main()
{
	return 0;
}
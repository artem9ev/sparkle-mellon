#include <iostream>

using namespace std;

int main()
{
	for (int j = 0; j < 5; j++)
	{
		int a[10];
		for (int i = 0; i < 10; i++)
		{
			cin >> a[i];
		}
		int pos, z;
		int i = 10, k, t;
		_asm {
			lea ebx, a
			mov edx, [ebx]
			mov z, edx; записал значение 1го элемента
			mov pos, ebx
			lea edx, a
			sub pos, edx
			add ebx, 4
			mov ecx, 9


			circleStart :
			cmp ecx, 0
				je circleEnd
				mov edx, [ebx]
				cmp edx, z
				jge leavee
				mov edx, [ebx]
				mov z, edx
				mov pos, ebx
				lea edx, a
				sub pos, edx
				leavee :
			add ebx, 4
				sub ecx, 1
				jmp circleStart

				circleEnd :

			mov edx, 0
				mov eax, pos
				mov bx, 4
				div bx
				mov pos, eax
		}
		cout << "min: " << z << " pos: " << pos << endl;
		_asm {
		circleUp:
			cmp i, 1
				je endCircleUp
				mov k, 10
				lea ebx, a
				circleDown :
			cmp k, 1
				je endCircleDown
				mov edx, [ebx]
				add ebx, 4
				mov eax, [ebx]
				cmp edx, eax
				jle notSwitch
				mov ecx, eax
				mov[ebx], edx
				sub ebx, 4
				mov[ebx], ecx
				add ebx, 4
				notSwitch:
			sub k, 1
				jmp circleDown
				endCircleDown :
			sub i, 1
				jmp circleUp
				endCircleUp :
		}
		for (int i = 0; i < 10; i++)
		{
			cout << a[i] << " ";
		}
		cout << endl << endl;
	}
    
}
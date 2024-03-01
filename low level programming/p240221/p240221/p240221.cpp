#include <iostream>

using namespace std;

int main()
{
    int a[10];
	for (int i = 0; i < 10; i++)
	{
		cin >> a[i];
	}
	int pos, z;
	int i, k;
	_asm {
		cicleUp:
		cmp i, 0
		je endCircleUp
			circleDown:
			cmp k, 0
			je endCircleDown

			endCircleDown:
		endCircleUp;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	/*_asm {
		lea ebx, a
		mov edx, [ebx]
		mov z, edx; записал значение 1го элемента
		add ebx, 4
		mov ecx, 9
		mov pos, ebx
		lea edx, a
		sub pos, edx

		circleStart: 
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
				leavee: 
			add ebx, 4
		sub ecx, 1
		jmp circleStart

		circleEnd:

		mov edx, 0
		mov eax, pos
		mov bx, 4
		div bx
		mov pos, eax		
	}*/
	cout << "z: " << z << " pos: " << pos;
}
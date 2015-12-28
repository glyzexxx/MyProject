#include <iostream>
#include <ctime>
#include <math.h>
#include <cstdlib>


using namespace std;
int prostoe_chislo()
{
	static time_t tval = time(0);
	tval += 10;
	int a, i = 0;
	srand(tval);
	while (1)
	{
		int z = 0;
		a = 1000 + rand() % 1000;
		for (int i = 2; i < a; i++)
		{
			if (a%i == 1)
				continue;
			if (a%i == 0)
			{
				z = 1;
				break;
			}
		}
		if ((z == 0)&&(a>100))
			break;
	}

	return a;
}

int bpow(int x, int n, int m)
{
	int count = 1;
	if (!n) return 1;
	while (n) {
		if (n % 2 == 0) {
			n /= 2;
			x *= x;
			x %= m;
		}
		else {
			n--;
			count *= x;
			count %= m;
		}
	}
	return count % m;
}
int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}

int main()
{
	long long p, Ka, Kb, n = 2, k = 0;
	long long Ea[55], Da[55], Eb[55], Db[55], otpA[55], otpB[55];
	long long provA[55], provB[55];
	//обнуление 
	for (int g = 0; g < 55; g++)
	{
		provA[g] = 0;
		provB[g] = 0;
	}
	srand(time(NULL));
	p = prostoe_chislo();
	cout <<"p="<< p << endl<<endl;
	while (k != 1)
	{
		Ka = rand() % 1000;
		k = gcd(Ka, (p - 1));
	}
	k = 0;
	while (k != 1)
	{
		Kb = rand() % 1000;
		k = gcd(Kb, (p - 1));
	}

	
	//шифрование карт от Алисы
	for (int i = 2; i < 55; i++)
	{
		Ea[i] = bpow(i, Ka, p);
	}
	
	//случайная последовательность карт от Алисы
	for (int i = 2; i < 55; i++)
	{
		while (true)
		{
			k = 2 + rand() % 54;
			if (provA[k] == 0)
			{
				otpA[i] = k;
				provA[k] = 1;
				break;

			}
		}
	}
	

		//первые случайне 5 карт от Боба
		for (int i = 2; i < 8; i++)
		{
			while (true)
			{
				k = 2 + rand() % 54;
				if (provB[k] == 0)
				{
					otpB[i] = k;
					provB[k] = 1;
					break;
				}
			}
		}

		//отправка Алисе
		cout << "\nOtpravlyaem 5 sluchainih kart ot A k B:\n";
		for (int i = 2; i < 8; i++)
		{
			cout << Ea[otpA[otpB[i]]] << " ";
		}
		cout << endl << endl;
		//нахождение za и zb
		long long Za = 1, Zb;
		int m = 1, j = 0, l;
		while (j != 1)
		{
			Za += 1;
			j = (Za*Ka) % (p - 1);
		}
		while (true)
		{
			j = (Ka*m) % (p - 1);
			if ((Ka*m) % (p - 1) == 1)
			{
				Za = m;
				break;
			}
			m++;

		}
		m = 1;
		while (true)
		{

			if ((Kb*m) % (p - 1) == 1)
			{
				Zb = m;
				break;
			}
			m++;
		}
		//cout << Za << endl;

		//расшифровка от Алисы
		for (int i = 2; i < 8; i++)
		{
			Da[i] = bpow(Ea[otpA[otpB[i]]], Za, p);

		}
		//Проверка расшифровки
		cout << "\nShifrovanie Alici:\n";
		for (int i = 2; i < 8; i++)
		{
			cout << Da[i]<<" ";
		}
		cout << endl << endl;
		//повторное обнуление
		for (int g = 0; g < 55; g++)
		{
			provB[g] = 0;
		}
		//вторые случайные 5 карт от Боба
		for (int i = 2; i < 8; i++)
		{
			while (true)
			{
				k = 2 + rand() % 54;
				if (provB[k] == 0)
				{
					otpB[i] = k;
					provB[k] = 1;
					break;
				}
			}
		}
		//Шифрование 5 карт ключом Боба и отправка Алисе
		cout << "\nBob shifruet 5 kart:\n";
		for (int i = 2; i < 8; i++)
		{
			Eb[i] = bpow(Ea[otpA[otpB[i]]], Kb, p);
			cout << Eb[i] << " ";
		}
		cout << endl << endl << "\nRashifrovka kluchom Alici i otpravka Boby:\n";
		//Расшифровка ключом Алисы и отправка Бобу
		for (int i = 2; i < 8; i++)
		{
			Db[i] = bpow(Eb[i], Za, p);
			cout << Db[i] << " ";
		}
		cout << endl<<endl << "\nRashifrovka Bobom:\n";
		//Расшифровка Бобом
		for (int i = 2; i < 8; i++)
		{
			Db[i] = bpow(Db[i], Zb, p);
			cout << Db[i] << " ";
		}


		cin >> p;
	}

#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

using namespace sf;

void getInterval(const Vector2f *axVertices, int numVert, const Vector2f &xAxis,
	float &min, float &max)
{
	min = max = (axVertices[0].x * xAxis.x + axVertices[0].y * xAxis.y);

	for (int i = 1; i<numVert; i++)
	{
		float d = (axVertices[i].x * xAxis.x + axVertices[i].y * xAxis.y);

		if (d<min) min = d;
		else if (d>max) max = d;
	}
}


bool IntervalIntersect(const Vector2f *A, int Anum, const Vector2f *B, int Bnum,
	const Vector2f &xAxis, const Vector2f &offset)
{
	float min0, max0;
	float min1, max1;

	getInterval(A, Anum, xAxis, min0, max0);
	getInterval(B, Bnum, xAxis, min1, max1);

	float h = offset.x * xAxis.x + offset.y*xAxis.y;
	min0 += h;
	max0 += h;

	float d0 = min0 - max1;
	float d1 = min1 - max0;

	if (d0 > 0.0f || d1 > 0.0f)
		return false;
	else
		return true;
}
bool pointInside(Vector2f point, Vector2f *vertices, int size)
{
	int i, j = 0;
	bool oddNODES = false;
	for (i = 0; i < size; i++)
	{
		j++;
		if (j == size)
			j = 0;
		if (vertices[i].y < point.y && vertices[j].y >= point.y || vertices[j].y < point.y && vertices[i].y >= point.y)
		{
			if (vertices[i].x + (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) *
				(vertices[j].x - vertices[i].x) < point.x)
			{
				oddNODES = !oddNODES;
			}
		}
	}
	return oddNODES;
}

bool check_collision(Vector2f *A, int sizeA,
	Vector2f *B, int sizeB, Vector2f &offset)
{
	if (!A || !B) return false;

	Vector2f xAxis[64];
	int iNumAxes = 0;

	//test dla A
	for (int j = sizeA - 1, i = 0; i<sizeA; j = i, i++)
	{
		Vector2f E0 = A[j];
		Vector2f E1 = A[i];
		Vector2f E = E1 - E0;

		xAxis[iNumAxes] = Vector2f(-E.y, E.x);

		if (!IntervalIntersect(A, sizeA, B, sizeB, xAxis[iNumAxes], offset))
			return false;

		iNumAxes++;
	}

	//test dla B
	for (int j = sizeB - 1, i = 0; i<sizeB; j = i, i++)
	{
		Vector2f E0 = B[j];
		Vector2f E1 = B[i];
		Vector2f E = E1 - E0;
		xAxis[iNumAxes] = Vector2f(-E.y, E.x);

		if (!IntervalIntersect(A, sizeA, B, sizeB, xAxis[iNumAxes], offset))
			return false;

		iNumAxes++;
	}

	return true;
}

bool check(sf::CircleShape & triangle, sf::RectangleShape & square)
{
	//std::vector <sf::RectangleShape> m_asteroids; // wektor na obikety Asteroid 

	// sprawdzenie asteroid
	//if (!m_asteroids.empty()) // sprawzamy czy wektor pusty 
	//{
		//Vector2f A[3] = { player.getPosition(0),player.getPosition(1),player.getPosition(2)};

		Vector2f A[3];

		for (int i = 0; i < 3; i++)
		{
			A[i] = triangle.getTransform().transformPoint(triangle.getPoint(i));
		}

		//wierzcho³ki poza wierzcho³kiem sodkowym 
		int numAsteroid = 0;
		//while (numAsteroid < 1) // 0 < ilosæ obiektów w wektorze 
		//{
			Vector2f *B = new Vector2f[4]; // iloœæ wierzcho³ków w obiekcie tablica 

			for (int i = 0; i < 4; i++)
			{
				B[i] = square.getTransform().transformPoint(square.getPoint(i));
				//B[i] = asteroids.getPoint(numAsteroid, i);
			}
			//uzupe³niamy tablicê B wspó³rzênymi punktów 


			bool collision; // flaga kolizji 

			for (int i = 0; i < 3; i++) // 3 razy bo trzy krawêdzie gracza
			{
				for (int j = 0; j < 4; j++) // tyle razy ile krawe¿i ma drugi obiekt 
				{
					collision = (check_collision(A, 3, B, 4, A[i] - B[j]));
					// flaga stanu = (tablica A, ilosæ, B, ilosæ, a[i] - b[j]); 

					if (collision) // true
					{
						break;
					}
				}

				if (collision)
				{
					//asteroids.del(numAsteroid); // zamiana mejsc etc w wektorze aseroids 
					
					//for (int i = numAsteroid; i<m_asteroids.size() - 1; i++)
					//{
						//std::swap(m_asteroids[i], m_asteroids[i + 1]);
					//}

					//m_asteroids.resize(m_asteroids.size() - 1);

					return true;
					break;
				}
			}

			delete[]B; // usuwamy dynamicznego taba 
			//numAsteroid++; // kolejny obiekt 
		//}
	//}

			return false;
}

bool check(sf::Vertex * tab, sf::RectangleShape & square)
{
	Vector2f A[2];

	for (int i = 0; i < 2; i++)
	{
		A[i] = tab[i].position;
	}

	Vector2f *B = new Vector2f[4];

	for (int i = 0; i < 4; i++)
	{
		B[i] = square.getTransform().transformPoint(square.getPoint(i));
	}

	bool collision; 

	for (int i = 0; i < 2; i++) 
	{
		for (int j = 0; j < 4; j++)  
		{
			collision = (check_collision(A, 2, B, 4, A[i] - B[j]));

			if (collision)
			{
				break;
			}
		}

		if (collision)
		{
			return true;
			break;
		}
	}

	delete[]B; 

	return false;
}



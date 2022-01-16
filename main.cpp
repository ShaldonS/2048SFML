#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

int main(int argc, char** argv) {
	sf::RenderWindow window;
	window.create(sf::VideoMode(600, 600), "2048");
	window.clear(sf::Color::White);

	sf::Texture square_texture;
	square_texture.loadFromFile("back.png");

	const int size_field = 16;
	float x_square = 10.f, y_square = 10.f;
	sf::RectangleShape squares[size_field];
	for (int i(1); i <= size_field; ++i) {
		squares[i - 1].setTexture(&square_texture);
		squares[i - 1].setSize(sf::Vector2f(136.0f, 136.0f));
		squares[i - 1].setPosition(sf::Vector2f(x_square, y_square));
		x_square += 136.0f;
		if (i % 4 == 0) {
			x_square = 10.0f;
			y_square += 136.0f;
		}
	}

	sf::Font font;
	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");

	sf::Text nums[size_field/4][size_field / 4];
	
	int x_nums = 136.0f / 2, y_nums = 136.0f / 2;
	for (int i(1); i <= size_field/4; ++i) {
		for (int j(1); j <= size_field / 4; ++j) {
			nums[i - 1][j - 1].setFont(font);
			nums[i - 1][j - 1].setCharacterSize(24);
			nums[i - 1][j - 1].setFillColor(sf::Color::Black);
			nums[i - 1][j - 1].setStyle(sf::Text::Bold);
			nums[i - 1][j - 1].setPosition(x_nums, y_nums);
			nums[i - 1][j - 1].setString(sf::String(""));
			x_nums += 136.0f;
		}
		x_nums = 10.0f + 136.0f / 2;
		y_nums += 136.0f;
	}
	//srand(time(NULL));
	/*int rand_num = rand() % size_field, check_num = rand_num;
	nums[rand_num].setString(sf::String(std::to_string(2)));
	rand_num = rand() % size_field;
	while (rand_num == check_num) {
		rand_num = rand() % size_field;
	}
	nums[rand_num].setString(sf::String(std::to_string(2)));*/
	nums[3][0].setString(sf::String(std::to_string(2)));
	nums[2][0].setString(sf::String(std::to_string(2)));

	while (window.isOpen()) {
		window.clear(sf::Color::White);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && ((event.key.code == sf::Keyboard::W) 
				|| (event.key.code == sf::Keyboard::A) 
				|| (event.key.code == sf::Keyboard::S)
				|| (event.key.code == sf::Keyboard::D))) {
				sf::String str2("2");
				sf::String str4("4");
				int i = 0, j = 0, first_i = 0, first_j = 0, second_i = 0, second_j = 0, range = size_field / 4;

				for (; i < range; ++i) {
					for (j = 0; j < range; ++j) {
						//std::cout << "\nTHIS ->" << i << " | " << j << "\n";
						if (event.key.code == sf::Keyboard::W) {
							if (!i) {
								continue;
							}
							first_i = i;
							first_j = j;
							second_j = j;
							int cnt = first_i, num = -1;
							while (cnt > 0) {
								if (nums[cnt][second_j].getString() == "") {
									num = cnt;
								}
								cnt--;
							}
							std::cout << "\nTHIS ->" << i << " | " << second_j << " | " << num << "\n";
							second_i = cnt;							
						}
						else if (event.key.code == sf::Keyboard::A) {
							if (!j) {
								continue;
							}
							first_i = i;
							first_j = j;
							second_i = i;
							int cnt = j - 1, cnt_exit = 0;
							while (cnt > 0) {
								if (nums[second_i][cnt].getString() == "") {
									cnt--;
								}
								cnt_exit++;
								if (cnt_exit > range - 1) {
									break;
								}
							}
							second_j = cnt;
						}
						else if (event.key.code == sf::Keyboard::S) {
							if (i == range - 1) {
								continue;
							}
							first_i = i;
							first_j = j;
							second_j = j;
							int cnt = first_i, num = -1;
							while (cnt < range - 1) {
								if (nums[cnt][second_j].getString() == "") {
									std::cout << "\nFINAL ->" << cnt << " | " << second_j << " | " << num << "\n";
									num++;
								}
								cnt++;
							}
							std::cout << "\nTHIS ->" << i << " | " << second_j << " | " << num << "\n";
							second_i = num;							
						}
						else if (event.key.code == sf::Keyboard::D) {
							if (!j) {
								continue;
							}
							first_i = i;
							first_j = j - 1;
							second_i = i;
							second_j = j;
						}
						//std::cout << "\n" << first_i << " - " << first_j << " | " << second_i << " - " << second_j << "\n";

						if (nums[first_i][first_j].getString() != "" && nums[second_i][second_j].getString() == "") {
							//nums[second_i][second_j].setString(nums[first_i][first_j].getString());
							nums[second_i][second_j].setString(nums[first_i][first_j].getString());
							nums[first_i][first_j].setString("");
							//nums[first_i][first_j].setString("");
							std::cout << "\nHELLO\n";
						}
						
					}
				}
			}
		}						/*if (nums[first_i][first_j].getString() == str2 && nums[second_i][second_j].getString() == str2) {	
							nums[first_i][first_j].setString(str4);
							nums[second_i][second_j].setString("");
						}*/
		for (int i(0); i < size_field; ++i) {
			window.draw(squares[i]);
		}
		for (int i(0); i < size_field / 4; ++i) {
			for (int j(0); j < size_field / 4; ++j) {
				window.draw(nums[i][j]);
			}
		}
		window.display();
	}


	return 0;
}



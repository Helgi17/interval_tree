#include <iostream>
#include "interval_map.h"
#include "interval.h"

using Interval = typename NSInterval::Interval<float>;
using KeyOfValue = typename NSInterval::KeyOfValue<float>;
using Compare = typename NSInterval::Compare;

/**
 * реализовать ассоциативный контейнер, 
 * ключами в котором будут интервалы объектов. 
 * Значениями - тоже объекты.
 *
 * В примере тип объектов - int
 */
using interval_map = NSIntervalMap::interval_map<Interval, char, KeyOfValue, Compare>;

void print(interval_map& m) {
	for (auto it=m.begin(); it != m.end(); ++it) {
		std::cout << (*it).y << " ";
	}
	std::cout << std::endl;
}

int main()
{
	interval_map imap;
	Interval i1(1.1, 10.2), i2(21.3,23.4), i3(0.5,0.5), i4(11.6, 21.6), i5(112.7);

	/** Операции вставки */
	imap[i1] = 'a';
	imap[{30.8, 32.9}] = 'b';
	imap.insert(i3, 'c');
	imap.insert(i2, 'd');
	imap.insert(i4, 'e'); /// <- Некорректная вставка
	imap.insert(i5, 'f');

	std::cout << "Insertions:" << std::endl;
	print(imap);

	/** Операции с итератором */
	std::cout << "Print second object " << (*(++imap.begin())).y << std::endl;

	/** Операции удаления */
	/// Удаление по итератору
	imap.erase((++imap.begin()));
	std::cout << "After erasing second objet" << std::endl;
	print(imap);

	/// Удаление по интервалу с точным совпадением
	imap.erase({30.8, 32.9});
	std::cout << "After erasing existing interval" << std::endl;
	print(imap);

	/// Удаление по итератору, найденному по точке
	imap.erase(imap.find(2.0));
	std::cout << "After erasing nonexisting interval with iterator containing single value" << std::endl;
	print(imap);

	/// Удаление по точке
	imap.erase(22.1);
	std::cout << "After erasing interval by single value" << std::endl;
	print(imap);

	/// Удаление по точке, если интервала, его содержащего нет
	imap.erase({10.2});
	std::cout << "After trying to erase nonexisting interval" << std::endl;
	print(imap);

	imap.erase(0.5);
	print(imap);

	imap.erase(112.7);
	print(imap);

	return 0;
}

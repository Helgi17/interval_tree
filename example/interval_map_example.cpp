#include <iostream>
#include "interval_map.h"
#include "interval.h"

using Interval = typename NSInterval::Interval<int>;
using KeyOfValue = typename NSInterval::KeyOfValue<int>;
using Compare = typename NSInterval::Compare;

/**
 * реализовать ассоциативный контейнер, 
 * ключами в котором будут интервалы объектов. 
 * Значениями - тоже объекты.
 *
 * В примере тип объектов - int
 */
using interval_map = NSIntervalMap::interval_map<Interval, int, KeyOfValue, Compare>;

void print(interval_map& m) {
	for (auto it=m.begin(); it != m.end(); ++it) {
		std::cout << (*it).y << " ";
	}
	std::cout << std::endl;
}

int main()
{
	interval_map imap;
	Interval i1(1, 10), i2(21,23), i3(0,0), i4(11, 21), i5(112);

	/** Операции вставки */
	imap[i1] = 1;
	imap[{30, 32}] = -2;
	imap.insert(i3, 3);
	imap.insert(i2, 2);
	imap.insert(i4, 5); /// <- Некорректная вставка
	imap.insert(i5, 6);

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
	imap.erase({30, 32});
	std::cout << "After erasing existing interval" << std::endl;
	print(imap);

	/// Удаление по итератору, найденному по точке
	imap.erase(imap.find(2));
	std::cout << "After erasing nonexisting interval with iterator containing single value" << std::endl;
	print(imap);

	/// Удаление по точке
	imap.erase(22);
	std::cout << "After erasing interval by single value" << std::endl;
	print(imap);

	/// Удаление по точке, если интервала, его содержащего нет
	imap.erase({10});
	std::cout << "After trying to erase nonexisting interval" << std::endl;
	print(imap);

	return 0;
}

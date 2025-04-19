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
	std::optional<Interval> i1 = Interval::create(1, 10);
	std::optional<Interval> i2 = Interval::create(21,23);
	std::optional<Interval> i3 = Interval::create(0,0);
	std::optional<Interval> i4 = Interval::create(11, 21);
	std::optional<Interval> i5 = Interval::create(112);
	std::optional<Interval> i6 = Interval::create(30, 32);

	/** Операции вставки */
	if (i1)	imap[*i1] = 1;
	if (i6) imap[*i6] = -2;
	if (i3) imap.insert(*i3, 3);
	if (i2) imap.insert(*i2, 2);
	if (i4) imap.insert(*i4, 5); /// <- Некорректная вставка
	if (i5) imap.insert(*i5, 6);

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
	if (i6) imap.erase(*i6);
	std::cout << "After erasing existing interval" << std::endl;
	print(imap);

	/// Удаление по итератору, найденному по точке
	std::optional<Interval> i7 = Interval::create(2);
	if (i7) imap.erase(imap.find(*i7));
	std::cout << "After erasing nonexisting interval with iterator containing single value" << std::endl;
	print(imap);

	/// Удаление по точке
	std::optional<Interval> i8 = Interval::create(22);
	if (i8) imap.erase(*i8);
	std::cout << "After erasing interval by single value" << std::endl;
	print(imap);

	/// Удаление по точке, если интервала, его содержащего нет
	std::optional<Interval> i9 = Interval::create(10);
	if (i9) imap.erase(*i9);
	std::cout << "After trying to erase nonexisting interval" << std::endl;
	print(imap);

	if (i3) imap.erase(*i3); // value 0
	print(imap);

	if (i5) imap.erase(*i5); // value 112
	print(imap);

	return 0;
}

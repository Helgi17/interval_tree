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
	std::optional<Interval> i1 = Interval::create(1.1, 10.2);
	std::optional<Interval> i2 = Interval::create(21.3,23.4);
	std::optional<Interval> i3 = Interval::create(0.5,0.5);
	std::optional<Interval> i4 = Interval::create(11.6, 21.6);
	std::optional<Interval> i5 = Interval::create(112.7);

	/** Операции вставки */
	if (i1) imap[*i1] = 'a';
	
	std::optional<Interval> i6 = Interval::create(30.8, 32.9);
	if (i6) imap[*i6] = 'b';
	if (i3) imap.insert(*i3, 'c');
	if (i2) imap.insert(*i2, 'd');
	if (i4) imap.insert(*i4, 'e'); /// <- Некорректная вставка
	if (i5) imap.insert(*i5, 'f');

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
	if (i6)imap.erase(*i6);
	std::cout << "After erasing existing interval" << std::endl;
	print(imap);

	/// Удаление по итератору, найденному по точке
	std::optional<Interval> i7 = Interval::create(2.0);
	if (i7) imap.erase(imap.find(*i7));
	std::cout << "After erasing nonexisting interval with iterator containing single value" << std::endl;
	print(imap);

	/// Удаление по точке
	std::optional<Interval> i8 = Interval::create(22.1);
	if (i8) imap.erase(*i8);
	std::cout << "After erasing interval by single value" << std::endl;
	print(imap);

	/// Удаление по точке, если интервала, его содержащего нет
	std::optional<Interval> i9 = Interval::create(10.2);
	if (i9) imap.erase(*i9);
	std::cout << "After trying to erase nonexisting interval" << std::endl;
	print(imap);

	if (i3) imap.erase(*i3);
	print(imap);

	if (i5) imap.erase(*i5);
	print(imap);

	return 0;
}

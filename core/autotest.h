/****************************************************************************************
** autotest.h is part of yoDownet
**
** Copyright 2013 Alireza Savand <alireza.savand@gmail.com>
**
** yoDownet is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** yoDownet is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

/*
 * This code has been taken from qtcreator blog:
 * http://qtcreator.blogspot.com/2009/10/running-multiple-unit-tests.html
 * To solve running multiple unit-tests problem when unit-testing Qt applications.
 * The only modification I've done on this code is code re-styling.
 *
 * Many Thanks to "Rob Caldecott";
 * http://www.blogger.com/profile/16139053405031925765
 */

#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <QtTest/QTest>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QSharedPointer>

namespace AutoTest {

typedef QList<QObject*> TestList;

inline TestList &testList()
{
    static TestList list;
    return list;
}

inline bool findObject(QObject *object)
{
    TestList &list = testList();

    if (list.contains(object))
        return true;

    foreach (QObject *test, list) {
        if (test->objectName() == object->objectName())
            return true;
    }

    return false;
}

inline void addTest(QObject *object)
{
    TestList &list = testList();

    if (!findObject(object))
        list.append(object);
}

inline int run(int argc, char *argv[])
{
    int ret = 0;

    foreach (QObject *test, testList())
        ret += QTest::qExec(test, argc, argv);

    return ret;
}

}

template <class T>
class Test
{
public:
    QSharedPointer<T> child;

    Test(const QString &name): child(new T)
    {
        child->setObjectName(name);
        AutoTest::addTest(child.data());
    }
};

#define DECLARE_TEST(className) static Test<className> t(#className);

#define TEST_MAIN \
    int main(int argc, char *argv[]) \
    { \
        return AutoTest::run(argc, argv); \
    }

#endif // AUTOTEST_H

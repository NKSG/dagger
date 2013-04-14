/*
 * Copyright (c) 2013 Hrvoje Zeba <zeba.hrvoje@gmail.com>
 *
 *    This file is part of dagger.
 *
 *    dagger is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once


#include <dagger/channel.h>


namespace dagger {


template<typename data>
class operation
{
public:
    virtual uint32_t render(data* d) = 0;
    
public:
    virtual ~operation()
    {
    }
};


template<typename data>
class unary_operation : public operation<data>
{
public:
    struct function
    {
        virtual ~function() {}
        virtual data operator()(const data& source) = 0;
    };

public:
    class cannot_connect_operation_error : public std::runtime_error
    {
    public:
        cannot_connect_operation_error()
          : runtime_error("cannot connect operation")
        {
        }
    };
    
public:
    unary_operation(operation<data>* parent, function* fn)
      : m_parent(parent)
      , m_function(fn)
      , m_last_change(0)
      , m_last_parent_change(0)
    {
        assert(parent != nullptr);
    }

    unary_operation(const data& d)
      : m_parent(nullptr)
      , m_function(nullptr)
      , m_data(d)
      , m_last_change(0)
      , m_last_parent_change(0)
    {
    }

public:
    uint32_t render(data* d)
    {
        if (m_parent == nullptr)
        {
            *d = m_data;
            return 1;
        }
        
        uint32_t last_parent_change = m_parent->render(d);
        
        if (last_parent_change == m_last_parent_change)
        {
            m_data_diff.apply(d);
            return m_last_change;
        }

        m_last_parent_change = last_parent_change;
            
        data r = m_function->operator()(*d);
        m_data_diff = data_diff(*d, r);
        
        *d = r;
        
        return ++m_last_change;
    }

    void connect(operation<data>* parent)
    {
        assert(parent != nullptr);

        if (m_parent == nullptr)
            throw cannot_connect_operation_error();

        m_parent = parent;
        m_last_parent_change = 0;
    }

private:
    typedef typename data::diff data_diff;
    
private:
    operation<data>* m_parent;
    
    function* m_function;
    
    data      m_data;
    data_diff m_data_diff;

    uint32_t m_last_change;
    uint32_t m_last_parent_change;
};

template<typename data>
class binary_operation : public operation<data>
{
public:
    struct function
    {
        virtual ~function() {}
        virtual data operator()(const data& source1, const data& source2) = 0;
    };

public:
    binary_operation(operation<data>* parent1, operation<data>* parent2, function* fn)
      : m_parent1(parent1)
      , m_parent2(parent2)
      , m_function(fn)
      , m_last_change(0)
    {
        assert(parent1 != nullptr);
        assert(parent2 != nullptr);
    }

public:
    uint32_t render(data* d)
    {
        data d1, d2;
        
        uint32_t last_parent1_change = m_parent1->render(&d1);
        uint32_t last_parent2_change = m_parent2->render(&d2);

        bool needs_update = false;

        needs_update |= last_parent1_change != m_last_parent1_change;
        needs_update |= last_parent2_change != m_last_parent2_change;

        if (needs_update == false)
        {
            *d = m_data;
            return m_last_change;
        }

        m_data = m_function->operator()(d1, d2);
        *d = m_data;
            
        return ++m_last_change;
    }

    void connect(operation<data>* parent1, operation<data>* parent2)
    {
        assert(parent1 != nullptr);
        assert(parent2 != nullptr);

        m_parent1 = parent1;
        m_parent2 = parent2;
        
        m_last_parent1_change = 0;
        m_last_parent1_change = 0;
    }

private:
    operation<data>* m_parent1;
    operation<data>* m_parent2;
    
    function* m_function;
    
    data      m_data;

    uint32_t m_last_change;
    uint32_t m_last_parent1_change;
    uint32_t m_last_parent2_change;
};

}

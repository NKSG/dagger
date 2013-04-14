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
    struct function
    {
        virtual ~function() {}
        virtual data operator()(const data& source) = 0;
    };

public:
    class invalid_alpha_channel_error : public std::runtime_error
    {
    public:
        invalid_alpha_channel_error()
          : runtime_error("alpha channel not compatible data")
        {
        }
    };
    
    class cannot_connect_operation_error : public std::runtime_error
    {
    public:
        cannot_connect_operation_error()
          : runtime_error("cannot connect operation")
        {
        }
    };
    
public:
    operation(operation* parent, function* fn)
      : m_function(fn)
      , m_parent(parent)
      , m_last_change(0)
      , m_last_parent_change(0)
    {
        assert(parent != nullptr);
    }

    operation(const data& d)
      : m_function(nullptr)
      , m_parent(nullptr)
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
        
        if (last_parent_change > m_last_parent_change)
        {
            m_last_parent_change = last_parent_change;
            
            do_function(d);
            return m_last_change;
        }
        
        m_data_diff.apply(d);
        return m_last_change;
    }

    void set_alpha(const channel& alpha)
    {
        if (m_parent == nullptr)
            throw invalid_alpha_channel_error();

        if (m_data_diff.height() != alpha.height())
            throw invalid_alpha_channel_error();
        
        if (m_data_diff.width() != alpha.width())
            throw invalid_alpha_channel_error();
        
        m_alpha = alpha;
        m_last_parent_change = 0;
    }

    void connect(operation* parent)
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
    void do_function(data* d)
    {
        data tmp(d->height(), d->width());

        data r = m_function->operator()(*d);
        r = algorithm::apply_alpha(r, *d, m_alpha);
        
        m_last_change++;
        
        m_data_diff = data_diff(*d, r);
        *d = tmp;
    }

private:
    function*  m_function;
    operation* m_parent;
    
    data    m_data;
    channel m_alpha;
    
    data_diff m_data_diff;

    uint32_t m_last_change;
    uint32_t m_last_parent_change;
};

}

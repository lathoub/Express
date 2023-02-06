    /*!
 *  @file       route.h
 *  Project     Arduino Express Library
 *  @brief      Fast, unopinionated, (very) minimalist web framework for Arduino
 *  @author     lathoub
 *  @date       20/01/23
 *  @license    GNU GENERAL PUBLIC LICENSE
 *
 *   Fast, unopinionated, (very) minimalist web framework for Arduino.
 *   Copyright (C) 2023 lathoub
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

class Route
    {
    public:
        using requestCallback = void (*)(Request &, Response &);
        using HandlerCallback = bool (*)(Request &, Response &);
        using DataCallback = void (*)(const Buffer &);
        using EndDataCallback = void (*)();

    private:
        static const char delimiter = '/';

    public: /// @brief
        DataCallback dataCallback_ = nullptr;

        /// @brief
        EndDataCallback endCallback_ = nullptr;

    public:
        Method method = Method::UNDEFINED;

        String path{};

        std::vector<HandlerCallback> handlers{}; 

        requestCallback fptrCallback = nullptr;

        // cache path splitting (avoid doing this for every request * number of paths)
        std::vector<PosLen> indices{}; 

    public:

        /// @brief 
        Route() {
#ifndef USE_STDCONTAINERS
            handlers.reserve(10); // TODO how many
            indices.reserve(10); // TODO how many
#endif
        }


        /// @brief
        /// @param path
        auto splitToVector(const String &path) -> void
        {
            splitToVector(path, indices);
        }

        /// @brief
        /// @param path
        /// @return
        static auto splitToVector(const String &path, std::vector<PosLen> &poslens) -> void
        {
            size_t p = 0, i = 1;
            for (; i < path.length(); i++)
            {
                if (path.charAt(i) == delimiter)
                {
                    poslens.push_back({p, i - p});
                    p = i;
                }
            }
            poslens.push_back({p, i - p});
        }

        /// @brief
        /// @param name
        /// @param callback
        auto on(const String &name, const DataCallback callback) -> void
        {
            LOG_I(F("register data callback"), name);
            dataCallback_ = callback;
            // return *this;
        }

        /// @brief
        /// @param name
        /// @param callback
        auto on(const String &name, const EndDataCallback callback) -> void
        {
            LOG_I(F("register end callback"), name);
            endCallback_ = callback;
            //  return *this;
        }
    };

#!/usr/bin/env lua5.3

--[[
MIT License

ltdd.lua
Copyright (c) 2020 Nick Trebes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
]]--

local function getDisplayString(value)
	local str = tostring(value)
	if type(value) == "string" then
		str = '"' .. str:gsub('"', '\\"') .. '"'
	end
	return str
end

local function constraintToString(self)
	return getmetatable(self).name
end

local function createConstraint(name, eval)
	return setmetatable({}, {
			__call = eval,
			__tostring = constraintToString,
			name = name
		})
end

local function constraintToStringWithVal(self)
	local meta = getmetatable(self)
	return meta.name .. getDisplayString(meta.value) .. ']'
end

local function createConstraintWithVal(name, value, eval)
	return setmetatable({}, {
			__call = function()
				return setmetatable({}, {
						__call = eval,
						__tostring = constraintToStringWithVal,
						name = tostring(name),
						value = value
					})
			end
		})
end

local function addTest(suite, name, test)
	getmetatable(suite).test[tostring(name)] = test
end

local function runSuite(suite, ...)
	local args, green, total = {...}, 0, 0
	local meta = getmetatable(suite)
	
	if #args > 0 then
		for i, name in ipairs(args) do
			total = total + 1
			name = tostring(name)
			
			if meta.test[name] then
				local ok, err = pcall(meta.test[name], suite)
				if ok then
					green = green + 1
				else
					print(meta.name .. ' -> ' .. name .. ':\n  ' .. tostring(err))
				end
			else
				print(meta.name .. ' -> ' .. name .. ': no such test')
			end
		end
	else
		for name, test in pairs(meta.test) do
			total = total + 1
			
			local ok, err = pcall(test, suite)
			if ok then
				green = green + 1
			else
				print(meta.name .. ' -> ' .. name .. ':\n  ' .. tostring(err))
			end
		end
	end
	
	print(meta.name .. ': ' .. tostring(green) .. ' of ' .. tostring(total) .. ' OK')
end

ltdd = {}

function ltdd.assertThat(actual, constraint)
	constraint = constraint()
	assert(constraint(actual), 'assertion failed: [' .. getDisplayString(actual) .. '] is not ' .. tostring(constraint))
end

function ltdd.assertThrows(fn, msg, ...)
	local info = debug.getinfo(fn, 'n')
	local ok, err = pcall(fn, ...)
	if ok then
		error('assertion failed: function ' .. tostring(info.name) .. ' failed to raise an error')
	elseif msg ~= nil then
		ltdd.assertThat(err, ltdd.isEqualTo(msg))
	end
end

function ltdd.createSuite(name)
	return setmetatable({}, {
		__call = runSuite,
		__index = ltdd,
		__newindex = addTest,
		name = name,
		test = {}
	})
end

function ltdd.isTrue()
	return createConstraint('[true]', function(self, actual)
			return actual and true
		end)
end

function ltdd.isFalse()
	return createConstraint('[false]', function(self, actual)
			return not (actual and true)
		end)
end

function ltdd.isNil()
	return createConstraint('[nil]', function(self, actual)
			return actual == nil
		end)
end

function ltdd.isNotNil()
	return createConstraint('[not nil]', function(self, actual)
			return actual ~= nil
		end)
end

function ltdd.isEqualTo(value)
	return createConstraintWithVal('[equal to] [', value, function(self, actual)
			return actual == getmetatable(self).value
		end)
end

function ltdd.isNotEqualTo(value)
	return createConstraintWithVal('[not equal to] [', value, function(self, actual)
			return actual ~= getmetatable(self).value
		end)
end

function ltdd.isGreaterThan(value)
	return createConstraintWithVal('[greater than] [', value, function(self, actual)
			return actual > getmetatable(self).value
		end)
end

function ltdd.isLessThan(value)
	return createConstraintWithVal('[less than] [', value, function(self, actual)
			return actual < getmetatable(self).value
		end)
end

function ltdd.isOfType(value)
	return createConstraintWithVal('[of type] [', value, function(self, actual)
			return type(actual) == getmetatable(self).value
		end)
end

function ltdd.assertTrue(actual)
	ltdd.assertThat(actual, ltdd.isTrue)
end

function ltdd.assertFalse(actual)
	ltdd.assertThat(actual, ltdd.isFalse)
end


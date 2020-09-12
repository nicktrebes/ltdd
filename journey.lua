#!/usr/bin/env lua5.3

require('ltdd')

local journey = ltdd.createSuite('journey')

function journey.isTrue_passes_on_eval_true(self)
	self.assertThat(true, self.isTrue)
end

function journey.isTrue_fails_on_eval_false(self)
	self.assertThrows(function()
			self.assertThat(false, self.isTrue)
		end)
end

function journey.isFalse_passes_on_eval_false(self)
	self.assertThat(false, self.isFalse)
end

function journey.isFalse_fails_on_eval_true(self)
	self.assertThrows(function()
			self.assertThat(true, self.isFalse)
		end)
end

function journey.isNil_passes_on_eval_nil(self)
	self.assertThat(nil, self.isNil)
end

function journey.isNil_fails_on_eval_not_nil(self)
	self.assertThrows(function()
			self.assertThat(false, self.isNil)
		end)
end

function journey.isNotNil_passes_on_eval_not_nil(self)
	self.assertThat(false, self.isNotNil)
end

function journey.isNotNil_fails_on_eval_nil(self)
	self.assertThrows(function()
			self.assertThat(nil, self.isNotNil)
		end)
end

function journey.isEqualTo_passes_on_equal(self)
	self.assertThat(1, self.isEqualTo(1))
end

function journey.isEqualTo_fails_on_not_equal(self)
	self.assertThrows(function()
			self.assertThat(1, self.isEqualTo(2))
		end)
end

function journey.isNotEqualTo_passes_on_not_equal(self)
	self.assertThat(1, self.isNotEqualTo(2))
end

function journey.isNotEqualTo_fails_on_equal(self)
	self.assertThrows(function()
			self.assertThat(1, self.isNotEqualTo(1))
		end)
end

function journey.isGreaterThan_passes_on_greater_than(self)
	self.assertThat(2, self.isGreaterThan(1))
end

function journey.isGreaterThan_fails_on_not_greater_than(self)
	self.assertThrows(function()
			self.assertThat(1, self.isGreaterThan(1))
		end)
end

function journey.isLessThan_passes_on_less_than(self)
	self.assertThat(1, self.isLessThan(2))
end

function journey.isLessThan_fails_on_not_less_than(self)
	self.assertThrows(function()
			self.assertThat(1, self.isLessThan(1))
		end)
end

function journey.isOfType_passes_on_correct_type_name(self)
	self.assertThat('hello', self.isOfType('string'))
end

function journey.isOfType_fails_on_incorrect_type_name(self)
	self.assertThrows(function()
			self.assertThat('hello', self.isOfType('table'))
		end)
end

function journey.assertTrue_passes_on_eval_true(self)
	self.assertTrue(true)
end

function journey.assertTrue_fails_on_eval_false(self)
	self.assertThrows(function()
			self.assertTrue(false)
		end)
end

function journey.assertFalse_passes_on_eval_false(self)
	self.assertFalse(false)
end

function journey.assertFalse_fails_on_eval_true(self)
	self.assertThrows(function()
			self.assertFalse(true)
		end)
end

function journey.assertNil_passes_on_nil(self)
	self.assertNil(nil)
end

function journey.assertNil_fails_on_not_nil(self)
	self.assertThrows(function()
			self.assertNil(false)
		end)
end

function journey.assertNotNil_passes_on_not_nil(self)
	self.assertNotNil(false)
end

function journey.assertNotNil_fails_on_nil(self)
	self.assertThrows(function()
			self.assertNotNil(nil)
		end)
end

function journey.assertEqual_passes_on_eval_equal(self)
	self.assertEqual(1, 1)
end

function journey.assertEqual_fails_on_eval_not_equal(self)
	self.assertThrows(function()
			self.assertEqual(1, 2)
		end)
end

journey(...)

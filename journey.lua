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

journey()

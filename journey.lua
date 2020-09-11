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

journey()

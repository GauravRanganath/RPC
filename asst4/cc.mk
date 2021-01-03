MAKEFLAGS += --no-builtin-rules

ALL_TARGETS = $(PROGS) $(SHARED_LIBS) $(STATIC_LIBS)
BUILD ?= Debug

all: $(addprefix $(BUILD)/,$(ALL_TARGETS))

define TARGET_RULE

$(BUILD)/$(1).objs/%.o: %.cc Makefile
	@echo "CXX $$< ($(BUILD)) for $(1)"
	@mkdir -p $$(dir $$@)
	@$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(BUILD)) $(CXXFLAGS_$(1)) $$< -MMD -MF $$(@:.o=.d) -c -o $$@

$(BUILD)/$(1).objs/%.o: %.cpp Makefile
	@echo "CXX $$< ($(BUILD)) for $(1)"
	@mkdir -p $$(dir $$@)
	@$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(BUILD)) $(CXXFLAGS_$(1)) $$< -MMD -MF $$(@:.o=.d) -c -o $$@

$(BUILD)/$(1).objs/%.o: %.c Makefile
	@echo "CC $$< ($(BUILD)) for $(1)"
	@mkdir -p $$(dir $$@)
	@$(CC) $(CFLAGS) $(CFLAGS_$(BUILD)) $(CFLAGS_$(1)) $$< -MMD -MF $$(@:.o=.d) -c -o $$@

$(BUILD)/objs/%.o: %.cc Makefile
	@echo "CXX $$< ($(BUILD))"
	@mkdir -p $$(dir $$@)
	@$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(BUILD)) $$< -MMD -MF $$(@:.o=.d) -c -o $$@

$(BUILD)/objs/%.o: %.cpp Makefile
	@echo "CXX $$< ($(BUILD))"
	@mkdir -p $$(dir $$@)
	@$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(BUILD)) $$< -MMD -MF $$(@:.o=.d) -c -o $$@

$(BUILD)/objs/%.o: %.c Makefile
	@echo "CC $$< ($(BUILD))"
	@mkdir -p $$(dir $$@)
	@$(CC) $(CFLAGS) $(CFLAGS_$(BUILD)) $$< -MMD -MF $$(@:.o=.d) -c -o $$@

endef

TARGET_OBJ_FILES = $(if $(or $(CFLAGS_$(1)),$(CXXFLAGS_$(1))),\
	$(addprefix $(BUILD)/$(1).objs/,$(addsuffix $(2),$(basename $(SRCS_$(1))))),\
	$(addprefix $(BUILD)/objs/,$(addsuffix $(2),$(basename $(SRCS_$(1))))))

TARGET_OBJ = $(call TARGET_OBJ_FILES,$(1),.o)
TARGET_OBJ_DEPS = $(call TARGET_OBJ_FILES,$(1),.d)
TARGET_DEPS = $(addprefix $(BUILD)/,$(DEPS_$(1)))

define PROG_TARGET_RULE

$(call TARGET_RULE,$(1))

$(BUILD)/$(1): $(call TARGET_OBJ,$(1)) $(call TARGET_DEPS,$(1))
	@echo LINK $$@
	@$(LD) $(LDFLAGS) $(LDFLAGS_$(BUILD)) $(LDFLAGS_$(1)) $(call TARGET_OBJ,$(1)) $(LIBS_$(1)) -o $$@
endef

ALL_PROGS_MK = $(foreach T,$(PROGS),$(BUILD)/$(T).mk)

-include $(foreach T,$(ALL_TARGETS),$(call TARGET_OBJ_DEPS,$T))

$(ALL_PROGS_MK): Makefile
	$(shell mkdir -p $(BUILD))
	$(file > $@,$(call PROG_TARGET_RULE,$(basename $(notdir $@))))
	@touch $@

include $(ALL_PROGS_MK)

clean:
	rm -rf $(BUILD) Debug Release
	rm -rf tester* *.log *~ *.json

realclean: clean
	rm -rf googletest

setup: realclean
	git clone https://github.com/google/googletest.git

.PHONY: all clean realclean setup

.SUFFIXES:

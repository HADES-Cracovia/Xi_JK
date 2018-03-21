
APP_NAME      := vertex_rec
SOURCE_FILES  := analysis.cc angles_ana.cc 
INSTALL_DIR   := .

USES_RFIO     := no
USES_ORACLE   := yes
USES_GFORTRAN := yes
HOME:=/u/knowakow


include $(HADDIR)/hades.def.mk

#LIB_DIRS += $(PLUTODIR) ${HOME}/usr/lib64
#INC_DIRS += ${HOME}/usr/include
#HYDRA_LIBS    += -lParticleEvent


.PHONY:  default
#default: clean build install
default: build install

include $(HADDIR)/hades.app.mk


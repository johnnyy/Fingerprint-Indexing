import parameters
from controller.controller import Controller

parameters.config()
params = parameters.parameters()

control = Controller()
control.exec(params)

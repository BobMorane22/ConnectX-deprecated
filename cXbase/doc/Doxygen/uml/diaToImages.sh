#!/bin/bash
for format in png eps # include more formats here, as needed...
do
	dia --export=uml.$format uml.dia
done

import time
from django.shortcuts import render

# Create your views here.
from django.http import HttpResponse


def greeting(request):
    return HttpResponse("Hello, world. You're at the my_app")


def time(request):
    import time
    return HttpResponse(f"Время в Москве:\t{time.ctime()}")

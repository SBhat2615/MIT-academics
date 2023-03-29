"""
Definition of urls for DjangoWebProject1.
"""

from django.contrib import admin
from django.urls import path
from django.conf.urls import include, url
urlpatterns = [

url('week/', include('week6example.urls')),
]
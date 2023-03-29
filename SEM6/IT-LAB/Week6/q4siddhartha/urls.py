
from django.urls import path
from . import views

urlpatterns = [
    path('', views.Firstpage, name='Firstpage'),
    path('Secondpage/', views.Secondpage, name='Secondpage'),
]

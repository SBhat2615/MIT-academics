from django.urls import path
from . import views

app_name = 'q1siddhartha'

urlpatterns = [
    path('', views.carform, name='carform'),
    path('carresult/', views.carresult, name='carresult'),
]
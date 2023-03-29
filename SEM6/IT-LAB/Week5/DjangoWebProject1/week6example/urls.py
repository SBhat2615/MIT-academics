
from django.conf.urls import url
from . import views 

urlpatterns = [ 
    url(r'^connection/',views.formView, name = 'formView'),
   url(r'^login/', views.login, name = 'login'),
  url(r'^logout/', views.logout, name = 'logout'), ]
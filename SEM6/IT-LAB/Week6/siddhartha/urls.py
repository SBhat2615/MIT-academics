"""
Definition of urls for siddhartha.
"""
from django.urls import include, path

urlpatterns = [
    path('q1siddhartha/', include('q1siddhartha.urls')),
    path('q2siddhartha/', include('q2siddhartha.urls')),
    path('q3siddhartha/', include('q3siddhartha.urls')),
    path('q4siddhartha/', include('q4siddhartha.urls')),
]

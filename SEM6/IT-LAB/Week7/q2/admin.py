from django.contrib import admin

# Register your models here.
from q2 import models

class WorksAdmin(admin.ModelAdmin):
    list_display = ('Name', 'Company', 'Salary')

class LivesAdmin(admin.ModelAdmin):
    list_display = ('Name', 'Street', 'City')

admin.site.register(models.Works, WorksAdmin)
admin.site.register(models.Lives, LivesAdmin)